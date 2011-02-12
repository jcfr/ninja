
#ifndef __win_compat_h
#define __win_compat_h

#include <io.h> // For _close, _open() and _mktemp_s()
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h> // For _mkdir and _getcwd

typedef int ssize_t;

#define PATH_MAX FILENAME_MAX

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

int open(const char* filename)
{
  return _open(filename, _O_RDWR | _O_TEXT);
}

int mkstemp (char *__template)
{
  int ret = _mktemp_s(__template, sizeof(__template));
  if(ret != 0)
    {
    return -1;
    }
  return open(__template);
}

#endif
