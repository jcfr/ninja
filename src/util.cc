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

#include "util.h"

#ifndef _WIN32
# include <execinfo.h>
#endif
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void DumpBacktrace(int skip_frames) {
#ifdef _WIN32
  printf("DumpBacktrace - Not implemented - See http://msdn.microsoft.com/en-us/library/ms680650.aspx");
#else
  void* stack[256];
  int size = backtrace(stack, 256);
  ++skip_frames;  // Skip ourselves as well.
  backtrace_symbols_fd(stack + skip_frames, size - skip_frames, 2);
#endif
}

void Fatal(const char* msg, ...) {
  va_list ap;
  fprintf(stderr, "FATAL: ");
  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  fprintf(stderr, "\n");
  DumpBacktrace(1);
  exit(1);
}
