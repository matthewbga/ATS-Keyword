#!/bin/bash

#  Copyright (c) 2021 Arm Limited. All rights reserved.
#  SPDX-License-Identifier: Apache-2.0
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

# Download dependencies, setup ml and apply patches.

NAME="$(basename "$0")"
HERE="$(dirname "$0")"
EXAMPLE=""
CLEAN=0

function sync_submodules {
    echo "Syncronising submodules" >&2
    git submodule init 2>&1 | grep -v 'registered'
    git submodule sync --recursive -q 2>&1 | grep -vE 'Skipping|Syncronising'
    git submodule update --recursive -q 2>&1 | grep -vE 'Skipping|Syncronising'

    # ( cd "lib/tf-m"                         && git fetch "https://gerrit.oss.arm.com/iot-sw/tf-m/internal/tf-m" refs/changes/47/203047/4 && git checkout FETCH_HEAD )
    ( cd "lib/amazon_freertos"              && git checkout 75d3feed1f498bda17b507ec66154e0d6621924e                                                     )
    ( cd "lib/mbedcrypto"                   && git checkout mbedtls-3.0.0                                                                                )
    ( cd "lib/mcuboot"                      && git checkout 4f80913                                                                                      )
    ( cd "lib/tfm_test"                     && git checkout e1a8c9f                                                                                      )
    ( cd "lib/VHT"                          && git checkout 01b55c0d72a88e4cdb5f5cfab835f6f4d1443d6f                                                     )
    ( cd "lib/ml-embedded-evaluation-kit"   && git checkout 69a4745c5178b0a1126a98bf077e2fd65241e1c6                                                     )    

    local tmp="$(mktemp)"
    find . -name '.git' >"$tmp"
    while read dir; do
        echo " * Syncronising submodule $dir" >&2
        pushd "$(dirname "$dir")" >/dev/null
        git submodule init 2>&1 | grep -v 'registered'
        git submodule sync --recursive -q 2>&1 | grep -vE 'Skipping|Syncronising'
        git submodule update --recursive -q 2>&1 | grep -vE 'Skipping|Syncronising'
        popd >/dev/null
    done <"$tmp"

    rm -f "$tmp"
}

function setup_ml_eval_kit {
    echo " * Downloading dependencies" >&2
    ML_KIT="$HERE/lib/ml-embedded-evaluation-kit"

    if [[ ! -e "$ML_KIT/.setup_complete" ]]; then 
        # Setup venv
        pushd "$ML_KIT" > /dev/null
        python3 set_up_default_resources.py

        # Download flatbuffers 
        pushd "dependencies/tensorflow/tensorflow/lite/micro/tools/make" > /dev/null
        mkdir downloads
        ./flatbuffers_download.sh $PWD/downloads

        # Download gemmlowp
        cd downloads
        curl -L https://github.com/google/gemmlowp/archive/fda83bdc38b118cc6b56753bd540caa49e570745.zip --output gemmlowp.zip
        unzip gemmlowp.zip
        mv gemmlowp-fda83bdc38b118cc6b56753bd540caa49e570745 gemmlowp
        rm gemmlowp.zip

        # Download ruy
        curl -L https://github.com/google/ruy/archive/4790797d11a81f96baf24f3731fd3ca44c2c5f8b.zip --output ruy.zip
        unzip ruy.zip
        mv ruy-4790797d11a81f96baf24f3731fd3ca44c2c5f8b ruy
        rm ruy.zip

        popd 

        # Generate models and labels 
        ML_GEN_SRC="generated/kws/src"
        ML_GEN_INC="generated/kws/include"
        ./resources_downloaded/env/bin/python3 -m pip install jinja2
        mkdir -p $ML_GEN_SRC
        mkdir -p $ML_GEN_INC
        ./resources_downloaded/env/bin/python3 scripts/py/gen_labels_cpp.py \
            --labels_file resources/kws/labels/ds_cnn_labels.txt \
            --source_folder_path $ML_GEN_SRC \
            --header_folder_path $ML_GEN_INC \
            --output_file_name ds_cnn_labels 
        ./resources_downloaded/env/bin/python3 scripts/py/gen_model_cpp.py \
            --tflite_path resources_downloaded/kws/ds_cnn_clustered_int8_vela_H128.tflite \
            --output_dir $ML_GEN_SRC
        popd

        touch $ML_KIT/.setup_complete
    fi
}

function apply_patches {
    local record="$HERE/patches/.patches-applied"
    touch "$record"
    for patch in $HERE/patches/*.patch; do
        local name="$(basename "$patch")"
        if grep "$name" "$record" >/dev/null; then
            echo " * Skipping $name" >&2
        else
            echo " * Applying $name" >&2
            patch -p1 -fi "$patch"
            echo "$name" >>"$record"
        fi
    done
}

sync_submodules
setup_ml_eval_kit
apply_patches
