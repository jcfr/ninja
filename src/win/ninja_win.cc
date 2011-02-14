
#include <windows.h> // For GetSystemInfo

int GetProcessorCount() {
  SYSTEM_INFO sysinfo;
  GetSystemInfo( &sysinfo );
  return sysinfo.dwNumberOfProcessors;
}
