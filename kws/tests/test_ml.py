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

import subprocess
from timeit import default_timer as timer
import subprocess, os
import pytest 

@pytest.fixture
def fvp_path():
    yield 'VHT-Corstone-300.x'

@pytest.fixture
def binary_path():
    yield os.getcwd() + '/../Objects'

@pytest.fixture
def vsi_script_path():
    yield os.getcwd() + '/../lib/VHT/audio/arm_vsi/audio_in/python'

@pytest.fixture(scope="function")
def fvp(fvp_path, binary_path, vsi_script_path):
    # Fixture of the FVP, when it returns, the FVP is started and 
    # traces are accessible through the .stdout of the object returned.
    # When the test is terminated, the FVP subprocess is closed.
    # Note: It can take few seconds to terminate the FVP 
    cmdline = [
        fvp_path, 
        '-a',  f'cpu_core.cpu0*={binary_path}/bl2.axf', 
        '--data', f'{binary_path}/tfm_s_signed.bin@0x38000000', 
        '--data', f'{binary_path}/tfm_ns_signed.bin@0x28060000', 
        '-C', 'cpu_core.mps3_board.visualisation.disable-visualisation=1', 
        '-C', 'cpu_core.mps3_board.telnetterminal0.start_telnet=0', 
        '-C', 'cpu_core.mps3_board.uart0.out_file=-', 
        '-C', 'cpu_core.mps3_board.uart0.unbuffered_output=1', 
        '-C', 'cpu_core.mps3_board.uart0.shutdown_on_eot=1',
        '-C', 'cpu_core.cpu0.semihosting-enable=1',
        '-C', 'cpu_core.mps3_board.DISABLE_GATING=1',
        '-V', f'{vsi_script_path}'
    ]

    proc = subprocess.Popen(cmdline, stdout=subprocess.PIPE)
    yield proc
    proc.terminate()
    proc.wait()

def test_ml(fvp):
    # Traces expected in the output 
    expectations = [
        'Starting bootloader',
        'Booting TFM v1.3.0',
        'Jumping to non-secure code...',
        'starting scheduler from ns main',
        'Ethos-U55 device initialised',
        'ML interface initialised',
        'INFO - For timestamp: 0.000000 (inference #: 0); label: on, score: 0.996094; threshold: 0.800000',
        'INFO - For timestamp: 0.500000 (inference #: 1); label: on, score: 0.996094; threshold: 0.800000',
        'INFO - For timestamp: 1.000000 (inference #: 2); label: on, score: 0.917969; threshold: 0.800000',
        'INFO - For timestamp: 1.500000 (inference #: 3); label: off, score: 0.996094; threshold: 0.800000',
        'INFO - For timestamp: 2.000000 (inference #: 4); label: <none>; threshold: 0.000000',
        'INFO - For timestamp: 2.500000 (inference #: 5); label: <none>; threshold: 0.000000',
        'INFO - For timestamp: 3.000000 (inference #: 6); label: go, score: 0.984375; threshold: 0.800000',
        'INFO - For timestamp: 3.500000 (inference #: 7); label: <none>; threshold: 0.000000',
        'INFO - For timestamp: 4.000000 (inference #: 8); label: <none>; threshold: 0.000000',
        'INFO - For timestamp: 4.500000 (inference #: 9); label: <none>; threshold: 0.000000',
        'INFO - For timestamp: 5.000000 (inference #: 10); label: _silence_, score: 0.996094; threshold: 0.800000',
    ]

    index = 0
    start = timer()
    current_time = timer()

    # Timeout for the test is 10 minutes 
    while (current_time - start) < (10 * 60):
        line = fvp.stdout.readline()
        if not line:
            break
        line = line.decode('utf-8')
        line = line.rstrip()
        print(line)
        if expectations[index] in line:
            index += 1
            if index == len(expectations):
                break
        current_time = timer()

    assert index == len(expectations)

