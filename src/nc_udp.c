#include "nc.h"

int
nc_udp_send(char *ip, char *port, char *body, int broadcast)
{
  int sock;
  struct sockaddr_in broadcast_addr;
  int broadcast_permission;
  char *send_str = body;
  unsigned int send_str_len;

  if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    return 1;

  if(broadcast == 1) {
    broadcast_permission = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
		  (void *) &broadcast_permission,
		  sizeof(broadcast_permission)) < 0)
      return 2;
  }

  memset(&broadcast_addr, 0, sizeof(broadcast_addr));
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_addr.s_addr = inet_addr(ip);
  broadcast_addr.sin_port = htons(atoi(port));

  send_str_len = strlen(send_str);

  if(sendto(sock, send_str, send_str_len, 0,
	    (struct sockaddr *) &broadcast_addr,
	    sizeof(broadcast_addr)) != send_str_len)
    return 3;

  return 0;
}

