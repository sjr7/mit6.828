#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(2, "usage: xargs <cmd> ...\n");
    exit(1);
  }

  int  i;
  int j;
  int k;
  int firstBlank;
  int length;
  char buf;
  int pid;
  char args[MAXARG][32];
  char *p[MAXARG];

  while (1)
  {
    i = 0;
    firstBlank = 0;
    memset(args, 0, MAXARG * 32);

    for (j = 0; j < argc; j++)
    {
      strcpy(args[i++], argv[j]);
    }

    j = 0;
    while (i < MAXARG - 1)
    {
      if ((length = read(0, &buf, 1)) <= 0) {
        exit(0);
      }

      if (buf == '\n') {
        break;
      }

      if (buf == ' ') {
        if (firstBlank) {
          i++;
          j = 0;
          firstBlank = -0;
        }
        continue;
      }
      args[i][j++] = buf;
      firstBlank = 1;
    }

    for (k = 0; k <= i; k++)
    {
      p[k] = args[k];
    }

    p[k] = 0;
    if ((pid = fork()) == 0) {
      exec(argv[1], p);
      exit(0);
    }
    wait(0);
  }
}


