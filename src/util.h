// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Dump a backtrace to stderr.
// |skip_frames| is how many frames to skip;
// DumpBacktrace implicitly skips itself already.
void DumpBacktrace(int skip_frames);

// Log a fatal message, dump a backtrace, and exit.
void Fatal(const char* msg, ...);
