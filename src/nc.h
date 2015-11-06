#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define HOST_MAX 20

typedef struct nc_opts {
  char host[HOST_MAX];
  int port;
  int secure;
  int verbose;
} nc_opts;

void nc_args_get_opts(nc_opts *opts, int argc, char **argv);
void nc_util_print_help();
