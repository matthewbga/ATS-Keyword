#!/usr/bin/env python3

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

import sys

ALLOWED_EXTS = ('.c','.h','.cc','.S','.sct','.cpp','.hpp','.cxx')
DISQUALIFIERS = ('units','tests','unit-test','downloads')

echo = False
for line in sys.stdin:
    line = line[:-1]
    if line.startswith('diff --git'):
        echo = False
        for ext in ALLOWED_EXTS:
            if line.endswith(ext):
                echo = True
                break
        for dq in DISQUALIFIERS:
            if dq in line:
                echo = False
                break
    if echo:
        print(line, file=sys.stdout)
