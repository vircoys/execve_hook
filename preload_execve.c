#define _GNU_SOURCE
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef int (*execve_func_t)(const char *__path, char *const __argv[], char *const __envp[]);

static execve_func_t old_execve = NULL;

int execve(const char *__path, char *const __argv[], char *const __envp[])
{
  old_execve = dlsym(RTLD_NEXT, "execve");

  if (strcmp(__path, "/usr/bin/python3") == 0)
  {

    for (int i = 0; __argv[i] != NULL; i++)
    {
      if (strcmp(__argv[i], "xxxxx_test.py") == 0)
      {
        printf("!!! execve hooked: /usr/bin/python3 xxxxx_test.py\n");
        return 0;
      }
    }
  }

  return old_execve(__path, __argv, __envp);
}