#include "nc.h"

static nc_shell_cmd cmds[SCMD_MAX];
static int cmd_current_code = 0;
static int current_room_sock;

static int func_cmd_help(char *cmd);
static int func_cmd_ping(char *cmd);
static int func_cmd_quit(char *cmd);
static int func_cmd_connect(char *cmd);
static int func_cmd_attach(char *cmd);

void
nc_shell_start(nc_opts *opts)
{
  fprintf(stdout, "NanoChat shell was started.\n");

  /* --- start of shell command registeration --- */
  nc_shell_register_cmd("/help", func_cmd_help);
  nc_shell_register_cmd("/ping", func_cmd_ping);
  nc_shell_register_cmd("/quit", func_cmd_quit);
  nc_shell_register_cmd("/connect", func_cmd_connect);
  nc_shell_register_cmd("/attach", func_cmd_attach);
  /* --- end of shell command registration --- */
  
  for(;;) {
    
    char *buf = NULL;
    size_t buf_size = 1024;
    int i;
    int found;

    found = 0;
    fprintf(stdout, ">> ");
    getline(&buf, &buf_size, stdin);
    

    if(buf[0] == '\n') {

      found = 1;

    } else {

      nc_utils_del_new_line(buf);
      for(i = 0; i < cmd_current_code; i++) {
	
	if(strstr(buf, cmds[i].name)) {
	  
	  if(cmds[i].func(buf) < 0) {
	    return;
	  }
	  
	  found = 1;
	  break;
	}
      
      }
      
    }

    if(!found)
      printf("Command not found!\n"
	     "Type '/help' to list available commands.\n");
    
  }
}

void
nc_shell_register_cmd(char *cmd_name, int (*func)(char *cmd))
{
  cmds[cmd_current_code].code = cmd_current_code;
  cmds[cmd_current_code].func = func;
  strcpy(cmds[cmd_current_code].name, cmd_name);
  
  cmd_current_code++;
}

int
func_cmd_help(char *cmd)
{
  printf("Available commands:\n"
	 "  /help                prints this text\n"
	 "  /ping                prints pong\n"
	 "  /quit                quit nanochat console\n"
	 "  /connect host port   connect to remote client\n"
	 "  /attach room         attach to room\n"
	 );

  return 0;
}

int
func_cmd_ping(char *cmd)
{
  printf("pong\n");
  return 0;
}

int
func_cmd_quit(char *cmd)
{
  printf("Bye!\n");
  return -1;
}

int
func_cmd_attach(char *cmd)
{
  int pair_raw_sock;
  int rc;

  rc = sscanf(cmd, "/attach %d", &pair_raw_sock);

  if(rc != 1) {
    printf("Error: correct format is 'attach room'.\n");
  }

  nc_log_writef("info", "Attached to room code: %d\n", pair_raw_sock);

  current_room_sock = pair_raw_sock;
  nc_otoc_start(pair_raw_sock);

  return 0;
}

int
func_cmd_connect(char *cmd)
{
  char host_req[HOST_MAX];
  char port_req[PORT_MAX];
  char url_req[URL_MAX];

  char host_pair[HOST_MAX];
  char port_pair[PORT_MAX];
  char url_pair[URL_MAX];

  int rc;  
  char *buf = NULL;
  int sock_req;
  int sock_pair;

  rc = sscanf(cmd, "/connect %s %s", host_req, port_req);

  if(rc != 2) {
    printf("Error: correct format is 'connect host port'.\n");
    return 1;
  }

  nc_utils_make_url(url_req, host_req, port_req);

  nc_log_writef("info", "One to one chat request to %s was issued.", url_req);

  sock_req = nn_socket(AF_SP, NN_REQ);
  nn_connect(sock_req, url_req);
  nn_send(sock_req, RCMD_OTOC, RCMD_LEN, 0);
  nn_recv(sock_req, &buf, NN_MSG, 0);
  nn_shutdown(sock_req, 0);

  strcpy(host_pair, host_req);
  strcpy(port_pair, buf);
  nn_freemsg(buf);

  nc_utils_make_url(url_pair, host_pair, port_pair);

  nc_log_writef("info", "One to one chat request was handshaked in %s.", url_pair);

  sock_pair = nn_socket(AF_SP, NN_PAIR);
  nn_connect(sock_pair, url_pair);
  
  current_room_sock = sock_pair;
  nc_otoc_start(sock_pair);

  return 0;
}
