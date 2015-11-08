#ifndef NC_H
#define NC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <pthread.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#define DEFAULT_DSCV_PORT "1881"

#define HOST_MAX 20
#define URL_MAX 30
#define PORT_MAX 6

typedef struct nc_opts {
  char host[HOST_MAX];
  char port[PORT_MAX];
  char url[URL_MAX];
  int secure;
  int verbose;
} nc_opts;

void nc_param_get_opts(nc_opts *opts, int argc, char **argv);
void nc_utils_print_help();
void nc_disco_start(nc_opts *opts);
void nc_shell_start(nc_opts *opts);

#endif
