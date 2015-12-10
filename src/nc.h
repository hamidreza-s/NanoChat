#ifndef NC_H
#define NC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>
#include <stdarg.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pair.h>

#define DISCO_PORT "1881" /* not changable */
#define DEFAULT_RPC_PORT "1991"
#define INIT_OTOC_PORT 1991

#define HOST_MAX 20
#define URL_MAX 30
#define PORT_MAX 6
#define NOW_STR_LEN 26
#define CONF_KEY_LEN 1024
#define CONF_VAL_LEN 1024

/* shell commands */
#define SCMD_NAME_LEN 32
#define SCMD_MAX 10

/* otoc shell commands */
#define OCMD_NAME_LEN 32
#define OCMD_MAX 10

/* discovery */
#define DCMD_LEN 8
#define DCMD_CODE_LEN 2
#define DCMD_PROB_REQUEST_CODE "01"
#define DCMD_PROB_RESPONSE_CODE "02"

/* rpc commands */
#define RCMD_LEN 2
#define RCMD_OTOC "01"

typedef struct nc_opts {
  char host[HOST_MAX];
  char broadcast[HOST_MAX];
  char port[PORT_MAX]; /* RPC port */
  char url[URL_MAX];
  int secure;
  int verbose;
} nc_opts;

typedef struct nc_conf_rec {
  char key[CONF_KEY_LEN];
  char val[CONF_VAL_LEN];
} nc_conf_rec;

typedef struct nc_shell_cmd {
  int code;
  char name[SCMD_NAME_LEN];
  int (*func)(char *cmd);
} nc_shell_cmd;

typedef struct nc_otoc_cmd {
  int code;
  char name[OCMD_NAME_LEN];
  int (*func)(char *cmd);
} nc_otoc_cmd;

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
void nc_utils_del_new_line(char *str);
int nc_utils_has_new_line(char *str);
void nc_utils_make_url(char *url, char *host, char *port);
int nc_utils_get_rec_sockfd(int sock);
void nc_utils_empty_string(char *str);
void nc_utils_die(char *str);

/* --- disco --- */
void nc_disco_start(nc_opts *opts);

/* --- rpc --- */
void nc_rpc_start(nc_opts *opts);

/* --- shell --- */
void nc_shell_start(nc_opts *opts);
void nc_shell_register_cmd(char *name, int (*func)(char *cmd));

/* --- one to one chat --- */
void nc_otoc_start(int pair_raw_sock);
void nc_otoc_register_cmd(char *name, int (*func)(char *cmd));

/* --- config --- */
void nc_conf_start();
void nc_conf_get(nc_conf_rec *conf_rec);

/* --- network interfaces --- */
int nc_netif_get_addrs(char *inet, char *broadcast);

#endif
