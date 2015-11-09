#include "nc.h"

void
nc_shell_start(nc_opts *opts)
{
  fprintf(stdout, "NanoChat shell was started.\n");
  
  for(;;) {
    
    char *buf = NULL;
    size_t buf_size = 1024;

    fprintf(stdout, ">> ");
    getline(&buf, &buf_size, stdin);
    printf("You said: %s", buf);
  }
}
