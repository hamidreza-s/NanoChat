#include "nc.h"

void*
nc_disco_loop(void *opts)
{
  int sock;
  
  struct sockaddr_in sock_local_addr;
  struct sockaddr_in sock_remote_addr;
  unsigned short sock_local_port;
  unsigned short sock_remote_port;
  
  socklen_t sock_remote_len = sizeof(sock_remote_addr);

  char recv_str[DCMD_LEN + 1];
  int recv_str_len;

  sock_local_port = atoi(DEFAULT_DISCO_PORT);
  memset(&sock_local_addr, 0, sizeof(sock_local_addr));
  sock_local_addr.sin_family = AF_INET;
  sock_local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  sock_local_addr.sin_port = htons(sock_local_port);

  if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    nc_utils_die("nc:disco:loop:sock");

  if(bind(sock, (struct sockaddr *) &sock_local_addr, sizeof(sock_local_addr)) < 0)
    nc_utils_die("nc:disco:loop:bind");

  nc_log_writef("info", "Disco was started.");

  for(;;) {
    
    if((recv_str_len = recvfrom(sock, recv_str, DCMD_LEN, 0,
				(struct sockaddr *) &sock_remote_addr,
				&sock_remote_len)) < 0)
      nc_utils_die("nc:disco:loop:recvfrom");

    sock_remote_port = ntohs(sock_remote_addr.sin_port);
    recv_str[recv_str_len] = '\0';

    nc_log_writef("info", "Discovery from %s:%d got: %s",
		  inet_ntoa(sock_remote_addr.sin_addr),
		  sock_remote_port,
		  recv_str);
    /*
      @TODO:
      catch the command (recv_str) and do appropriate action
     */

  }
}

void
nc_disco_prob()
{
  /*
    @TODO: implement it
   */
}

void
nc_disco_start(nc_opts *opts)
{
  pthread_t disco_loop;
  pthread_create(&disco_loop, NULL, nc_disco_loop, opts);
}
