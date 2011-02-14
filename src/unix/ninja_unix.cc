

int GetProcessorCount() {
  int processors = 2;

  const char kProcessorPrefix[] = "processor\t";
  char buf[16 << 10];
  FILE* f = fopen("/proc/cpuinfo", "r");
  if (!f)
    return processors;
  while (fgets(buf, sizeof(buf), f)) {
    if (strncmp(buf, kProcessorPrefix, sizeof(kProcessorPrefix) - 1) == 0)
      ++processors;
  }
  fclose(f);
  
  return processors;
}
