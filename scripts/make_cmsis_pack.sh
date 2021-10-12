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

# This creates a cmsis pack based on a bootstrapped repo. Requires 7z.

PWD=$(pwd)
PWD=${PWD%/*} # get parent path
PWD=${PWD##*/} # get the dir name

7z a -tzip ARM.DevSummitDemo.1.0.0.pack ../../${PWD} \
-xr'!.*' \
-xr'!*.xml' \
-xr'!*.html' \
-xr'!*.htm' \
-xr'!*.js' \
-xr'!*.pbtxt' \
-xr'!*.swift' \
-xr'!*.go' \
-xr'!*.java' \
-xr'!*.php' \
-xr'!*.pb' \
-x"!${PWD}/RTE" \
-x"!${PWD}/build" \
-x"!${PWD}/ci" \
-x"!${PWD}/lib/amazon_freertos/doc" \
-x"!${PWD}/lib/amazon_freertos/projects" \
-x"!${PWD}/lib/amazon_freertos/tests" \
-x"!${PWD}/lib/amazon_freertos/tools" \
-x"!${PWD}/lib/amazon_freertos/vendors" \
-x"!${PWD}/lib/amazon_freertos/libraries/3rdparty/CMock" \
-x"!${PWD}/lib/amazon_freertos/libraries/3rdparty/unity" \
-x"!${PWD}/lib/amazon_freertos/libraries/ble" \
-x"!${PWD}/lib/amazon_freertos/libraries/lwip" \
-x"!${PWD}/lib/amazon_freertos/libraries/lwip_osal" \
-x"!${PWD}/lib/amazon_freertos/libraries/tinycrypt" \
-x"!${PWD}/lib/amazon_freertos/libraries/tracealyzer_recorder" \
-x"!${PWD}/lib/amazon_freertos/libraries/win_pcap" \
-x"!${PWD}/lib/amazon_freertos/libraries/coreMQTT-Agent/test" \
-x"!${PWD}/lib/amazon_freertos/libraries/coreMQTT/test" \
-x"!${PWD}/lib/amazon_freertos/libraries/coreHTTP/test" \
-x"!${PWD}/lib/amazon_freertos/libraries/abstractions/pkcs11/corePKCS11/test" \
-x"!${PWD}/lib/mcuboot/boot/cypress" \
-x"!${PWD}/lib/mcuboot/ext/mbedtls/tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/resources_downloaded" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DAP" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Documentation" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/ComputeLibrary" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/DSP_Lib_TestSuite" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Projects" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Toolchain" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Platforms" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Scripts" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Examples" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/Testing" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DSP/PythonWrapper" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DoxyGen" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Pack" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/NN/NN_Lib_Tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/NN/Tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/NN/Scripts" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/NN/Examples" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/CoreValidation/Source" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/CoreValidation/Tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/RTOS2/Source" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/RTOS2/Template" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/RTOS2/RTX" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Utilities" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Core_A/Source" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Core/Template" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/RTOS" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/DAP" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Driver/DriverTemplates" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/CMSIS/Driver/VIO" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/compiler" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/java" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/go" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/python" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/stream_executor" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/tools" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/ios" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/experimental" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/tutorials" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/java" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/profiling" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/g3doc" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/testdata" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/swift" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/tools" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/examples" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/python" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/testing" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/samples" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/micro/tools/make/downloads/gemmlowp/test" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/micro/examples" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/core/kernels/fuzzing" \
-x"!${PWD}/lib/VHT/DoxyGen" \
-x"!${PWD}/lib/tfm_test/test" \
-x"!${PWD}/lib/tf-m/platform/ext/target/arm/mps2" \
-x"!${PWD}/lib/tf-m/platform/ext/target/arm/musca_b1" \
-x"!${PWD}/lib/tf-m/platform/ext/target/arm/musca_s1" \
-x"!${PWD}/lib/tf-m/platform/ext/target/cypress" \
-x"!${PWD}/lib/tf-m/platform/ext/target/cypress" \
-x"!${PWD}/lib/tf-m/platform/ext/target/lairdconnectivity" \
-x"!${PWD}/lib/tf-m/platform/ext/target/nordic_nrf" \
-x"!${PWD}/lib/tf-m/platform/ext/target/nuvoton" \
-x"!${PWD}/lib/tf-m/platform/ext/target/nxp" \
-x"!${PWD}/lib/tf-m/platform/ext/target/stm" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/tensorflow/tensorflow/lite/objc" \
-x"!${PWD}/lib/mbedcrypto/tests" \
-x"!${PWD}/lib/ml-embedded-evaluation-kit/dependencies/cmsis/ARM.CMSIS.pdsc" \
-x"!${PWD}/scripts"

7z a -tzip ARM.DevSummitDemo.1.0.0.pack ./ARM.DevSummitDemo.pdsc
