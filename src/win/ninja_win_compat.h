
#ifndef __win_compat_h
#define __win_compat_h

#include <io.h> // For _close
#include <direct.h> // For _mkdir and _getcwd

typedef int ssize_t;

int close(int fd)
{
  return _close(fd);
}

int mkdir(const char *__path, int /*unused */)
{
  return _mkdir(__path);
}

char * getcwd (char *__buf, size_t __size)
{
  return _getcwd(__buf, __size);
}

int isatty(int fd)
{
  return _isatty(fd);
}

#endif
