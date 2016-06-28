#include "nc.h"

#define ROOMS_HASH_TABLE "otoc"
#define PEERS_HASH_TABLE "peers"

static vedis *vedis_ptr;

int nc_dal_print_array(char* cmd);

void
nc_dal_start(nc_opts *opts)
{
  int rc;

  rc = vedis_open(&vedis_ptr, ":mem:");
  if(rc != VEDIS_OK) {
    nc_utils_die("nc:dal:start:open");
  }

  nc_log_writef("info", "Data Access Layer has been started.");
}

int
nc_dal_save_room(int room_code)
{
  int rc;
  char time_str[NOW_STR_LEN];

  nc_utils_now_str(time_str);
  
  rc = vedis_exec_fmt(vedis_ptr, "HSET %s '%d' '%s'",
		      ROOMS_HASH_TABLE, room_code, time_str);

  if(rc != VEDIS_OK) {
    nc_utils_die("nc:dal:save:otoc");
  }

  return 0;
}

int
nc_dal_save_peer(char **record)
{
  int rc;
  char time_str[NOW_STR_LEN];
  
  nc_utils_now_str(time_str);

  rc = vedis_exec_fmt(vedis_ptr, "HSET %s '%s' '%s'",
		      PEERS_HASH_TABLE, *record, time_str);

  if(rc != VEDIS_OK) {
    nc_utils_die("nc:dal:set:peer");
  }

  return 0;
}

int
nc_dal_print_peers()
{
  char cmd[32] = "HKEYS ";
  strcat(cmd, PEERS_HASH_TABLE); 
  if(nc_dal_print_array(cmd))
    fprintf(stdout, "[-] No peers!\n");

  return 0;
}

int
nc_dal_print_rooms()
{
  char cmd[32] = "HKEYS ";
  strcat(cmd, ROOMS_HASH_TABLE);
  if(nc_dal_print_array(cmd))
    fprintf(stdout, "[-] No rooms!\n");

  return 0;
}
int
nc_dal_print_array(char *cmd)
{
  int rc;
  vedis_value *result_ptr;

  rc = vedis_exec(vedis_ptr, cmd, -1);
  if(rc != VEDIS_OK)
    nc_utils_die("nc:dal:print:array:execute");

  rc = vedis_exec_result(vedis_ptr, &result_ptr);
  if(rc != VEDIS_OK)
    nc_utils_die("nc:dal:print:array:result");

  if(vedis_value_is_null(result_ptr)) {
    
    return 1;

  } else if(vedis_value_is_array(result_ptr)) {

    vedis_value *entry_ptr;

    while((entry_ptr = vedis_array_next_elem(result_ptr)) != 0) {
      
      if(!vedis_value_is_null(entry_ptr)) {

	const char *result_str = vedis_value_to_string(entry_ptr, 0);
	fprintf(stdout, "[+] %s\n", result_str);
	
      }
    }

  } else {

    const char *result_str;
    result_str = vedis_value_to_string(result_ptr, 0);
    fprintf(stdout, "[+] %s\n", result_str);
    return 0;

  }

  return 0;
}
