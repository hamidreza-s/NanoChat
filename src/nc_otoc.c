#include "nc.h"

void
nc_otoc_start(int pair_raw_sock)
{
  int shell_fd_sock;
  int pair_fd_sock;

  fd_set readfds;
  int maxfds;
  char time_str[NOW_STR_LEN];

  enum {sent, received, none} last_action = none;

  shell_fd_sock = fileno(stdin);
  pair_fd_sock = nc_utils_get_rec_sockfd(pair_raw_sock);
  maxfds = pair_fd_sock + 1;

  for(;;) {

    switch(last_action) {
    case none: 
      fprintf(stdout, ">> Entering (room code %d) ...\n", pair_raw_sock);
      fprintf(stdout, ">>> ");
      fflush(stdout); 
      break;
    case received: 
      fprintf(stdout, ">>> ");
      fflush(stdout); 
      break;
    case sent: 
      fprintf(stdout, ">>> "); 
      fflush(stdout); 
      break;
    }

    FD_ZERO(&readfds);
    FD_SET(pair_fd_sock, &readfds);
    FD_SET(shell_fd_sock, &readfds);

    select(maxfds, &readfds, NULL, NULL, NULL);

    if(FD_ISSET(shell_fd_sock, &readfds)) {      

      char *buf = NULL;
      size_t buf_sz = 1024;

      nc_utils_now_str(time_str);      
      getline(&buf, &buf_sz, stdin);

      if(buf[0] != '\n') {
	nn_send(pair_raw_sock, buf, strlen(buf), 0);
	fprintf(stdout, "[%s] >>> %s", time_str, buf);
	fflush(stdout);
	nc_utils_del_new_line(buf);
	nc_log_writef("debug", "sent: %s", buf);
	nc_utils_empty_string(buf);
      }

      /* 
	 @TODO: 
	 close socket and break shell if
	 user types /leave
      */

      last_action = sent;

    } else if(FD_ISSET(pair_fd_sock, &readfds)) {

      char *buf = NULL;

      nc_utils_now_str(time_str);
      nn_recv(pair_raw_sock, &buf, NN_MSG, 0);
      fprintf(stdout, "\r[%s] <<< %s", time_str, buf);
      fflush(stdout);
      nc_utils_del_new_line(buf);
      nc_log_writef("debug", "received: %s", buf);
      nc_utils_empty_string(buf);
      nn_freemsg(buf);
      last_action = received;
    }

  }

}
