#include "nc.h"

static FILE *conf_fp;

void
nc_conf_start()
{
  conf_fp = fopen("./var/nanochat.conf", "r");
}

void
nc_conf_get(nc_conf_rec *conf_rec)
{
  char *buf = NULL;
  size_t buf_size = CONF_KEY_LEN + CONF_VAL_LEN + 2;

  while(getline(&buf, &buf_size, conf_fp) != -1) {
    
    char *key_val;
    char *new_line;

    if((key_val = strstr(buf, conf_rec->key)) != NULL) {
      
      strcpy(conf_rec->val, strchr(buf, '=') + 1);
      
      if((new_line = strchr(conf_rec->val, '\n')) != NULL) {
	*new_line = '\0';
      }

      break;

    }
  }
}
