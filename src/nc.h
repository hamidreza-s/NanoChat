#ifndef NC_H
#define NC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#define DEFAULT_DSCV_PORT "1881"
#define HOST_MAX 20
#define URL_MAX 30
#define PORT_MAX 6
#define NOW_STR_LEN 26
#define CONF_KEY_LEN 1024
#define CONF_VAL_LEN 1024

typedef struct nc_opts {
  char host[HOST_MAX];
  char port[PORT_MAX];
  char url[URL_MAX];
  int secure;
  int verbose;
} nc_opts;

typedef struct nc_conf_rec {
  char key[CONF_KEY_LEN];
  char val[CONF_VAL_LEN];
} nc_conf_rec;

/* --- parameters --- */
void nc_param_get_opts(nc_opts *opts, int argc, char **argv);

/* --- logger --- */
void nc_log_start();
void nc_log_write(const char *tag, const char *msg);
void nc_log_writef(const char *tag, const char *msgf, ...);

/* --- utilities --- */
void nc_utils_print_help();
int nc_utils_count_char(const char *str, const char chr);
void nc_utils_now_str(char *time_str);

/* --- discovery --- */
void nc_disco_start(nc_opts *opts);

/* --- shell --- */
void nc_shell_start(nc_opts *opts);

/* --- config --- */
void nc_conf_start();
void nc_conf_get(nc_conf_rec *conf_rec);

#endif
