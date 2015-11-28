#include "nc.h"

void*
nc_rpc_loop(void *void_opts)
{
  nc_opts *opts = (nc_opts*) void_opts;
  int sock = nn_socket(AF_SP, NN_REP);
  nn_bind(sock, opts->url);
  nc_log_writef("info", "RPC was started on URL: %s.\n", opts->url);
  
  for(;;) {
    char *buf = NULL;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);
    int cmp_rc;
    
    nc_log_writef("info", "Incoming RPC request: %s\n", buf);

    cmp_rc = strcmp(buf, RCMD_OTOC);

    if(cmp_rc == 0 && bytes == RCMD_LEN) {

      /* one to one chat */
      
      char otoc_url[URL_MAX];
      static int otoc_port_init = INIT_OTOC_PORT;
      char otoc_port[PORT_MAX];
      int otoc_sock = nn_socket(AF_SP, NN_PAIR);

      sprintf(otoc_port, "%d", otoc_port_init++);
      nc_utils_make_url(otoc_url, opts->host, otoc_port);
      nn_bind(otoc_sock, otoc_url);

      nc_log_writef("info", "New oto chat was connected on URL: %s.\n", otoc_url);
      nn_send(sock, otoc_port, (int) strlen(otoc_port), 0);

      fprintf(stdout, 
	      "[Notification]: Incoming one to one chat (room code %d).\n>> ",
	      otoc_sock);
      fflush(stdout);

    } else {

      /* unknown command */
      
      nn_send(sock, buf, bytes, 0);
    }

    nc_utils_empty_string(buf);
    nn_freemsg(buf);
  }
  return NULL;
}

void
nc_rpc_start(nc_opts *opts)
{
  pthread_t rpc_loop;
  pthread_create(&rpc_loop, NULL, nc_rpc_loop, opts);
}
