#include "nc.h"

void
nc_shell_start(nc_opts *opts)
{
  printf("NanoChat shell was started.\n");
  
  for(;;) {
    
    char *buf = NULL;
    size_t buf_size = 1024;

    printf(">> ");
    getline(&buf, &buf_size, stdin);
    printf("You said: %s", buf);
  }
}
