#include "nc.h"

int
nc_names_get_hostname(char *buf, int len)
{
  gethostname(buf, len);
  return 0;
}

int
nc_names_get_username(char *buf, int len)
{
  struct passwd *pw;
  uid_t uid;

  uid = geteuid();
  pw = getpwuid(uid);
  if(pw) {
    strcpy(buf, pw->pw_name);
    return 0;
  }

  return 1;
}
