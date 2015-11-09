#include "nc.h"

void*
nc_disco_loop(void *void_opts)
{
  nc_opts *opts = (nc_opts*) void_opts;
  int sock = nn_socket(AF_SP, NN_REP);
  nn_bind(sock, opts->url);
  nc_log_writef("info", "Discovery responder was started on URL: %s.\n", opts->url);
  for(;;) {
    char *buf = NULL;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);
    nn_send(sock, buf, bytes, 0);
    nn_freemsg(buf);
  }
  return NULL;
}

void
nc_disco_start(nc_opts *opts)
{
  pthread_t dscv_loop;
  pthread_create(&dscv_loop, NULL, nc_disco_loop, opts);
}
