#include "nc.h"

void
nc_msg_encode(int head_len, int body_len, char *head, char *body, char **buf)
{
  *buf = (char*) malloc(head_len + body_len + 3);
  sprintf(*buf, "%d %s %d %s", head_len, head, body_len, body);
}

void
nc_msg_free(char *buf)
{
  free(buf);
}
