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

#filters output
import subprocess
from timeit import default_timer as timer
import os
import pytest 

@pytest.fixture
def fvp_path():
    yield '/opt/FVP_Corstone_SSE-300_Ethos-U55/models/Linux64_GCC-6.4/FVP_Corstone_SSE-300_Ethos-U55'

@pytest.fixture
def binary_path():
    yield os.getcwd() + '/../Objects'

@pytest.fixture(scope="function")
def fvp(fvp_path, binary_path):
    # Fixture of the FVP, when it returns, the FVP is started and 
    # traces are accessible through the .stdout of the object returned.
    # When the test is terminated, the FVP subprocess is closed.
    # Note: It can take few seconds to terminate the FVP 
    cmdline = [
        fvp_path, 
        '-a',  f'cpu0*={binary_path}/bl2.axf', 
        '--data', f'{binary_path}/tfm_s_signed.bin@0x01000000', 
        '--data', f'{binary_path}/tfm_ns_signed.bin@0x01060000', 
        '-C', 'mps3_board.visualisation.disable-visualisation=1', 
        '-C', 'mps3_board.telnetterminal0.start_telnet=0', 
        '-C', 'mps3_board.visualisation.disable-visualisation=1', 
        '-C', 'mps3_board.uart0.out_file=-', 
        '-C', 'mps3_board.uart0.unbuffered_output=1', 
        '-C', 'mps3_board.uart0.shutdown_on_eot=1'
    ]
    proc = subprocess.Popen(cmdline, stdout=subprocess.PIPE)
    yield proc
    proc.terminate()
    proc.wait()

def test_blinky(fvp):
    # Traces expected in the output 
    expectations = [
        'Starting bootloader',
        'Booting TFM v1.3.0',
        'FreeRTOS main task started',
        'LED on',
        'LED off',
        'LED on',
        'LED off',
        'LED on',        
    ]

    index = 0
    start = timer()
    current_time = timer()

    # Timeout for the test is 20 seconds 
    while (current_time - start) < 20:
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

    
