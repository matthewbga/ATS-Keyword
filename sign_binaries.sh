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

set -e

case "$1" in
    kws)    ;;
    blinky) ;;
    *)
        echo "Usage: $0 <blinky|kws>" >&2
        exit 1
        ;;
esac

EXAMPLE=$1

# create binary files of secure and non secure build outputs
echo "Extracting binaries from axf files."
fromelf --bin --output="build/secure_partition/tfm_s_unsigned.bin" "build/secure_partition/tfm_s.axf" --bincombined
fromelf --bin --output="build/$EXAMPLE/tfm_ns_unsigned.bin" "build/$EXAMPLE/tfm_ns.axf" --bincombined

# sign with parameters extracted of tfm cmake build
echo "Signing secure binary."
python3 ./lib/tf-m/bl2/ext/mcuboot/scripts/wrapper/wrapper.py \
        -v 1.3.0 \
        --layout $(readlink -f "bsp/signing_layout_s.c") \
        -k ./lib/tf-m/bl2/ext/mcuboot/root-RSA-2048.pem \
        --public-key-format full \
        --align 1 \
        --pad \
        --pad-header \
        -H 0x400 \
        -s auto \
        "build/secure_partition/tfm_s_unsigned.bin" \
        "build/secure_partition/tfm_s_signed.bin"

echo "Signing non-secure binary."
python3 ./lib/tf-m/bl2/ext/mcuboot/scripts/wrapper/wrapper.py \
        -v 1.0.0 \
        --layout $(readlink -f "bsp/signing_layout_ns.c") \
        -k ./lib/tf-m/bl2/ext/mcuboot/root-RSA-2048_1.pem  \
        --public-key-format full \
        --align 1 \
        --pad \
        --pad-header \
        -H 0x400 \
        -s auto \
        "build/$EXAMPLE/tfm_ns_unsigned.bin" \
        "build/$EXAMPLE/tfm_ns_signed.bin"

echo "Signed binaries ready to be run in FVP."
echo ""
echo "Use the ./run.sh script to run the FVP."
