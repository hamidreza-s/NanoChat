#include "nc.h"

static nc_shell_cmd cmds[SCMD_MAX];
static int cmd_current_code = 0;
static int current_room_sock;

void func_cmd_help(char *cmd);
void func_cmd_ping(char *cmd);
void func_cmd_connect(char *cmd);
void func_cmd_attach(char *cmd);

void
nc_shell_start(nc_opts *opts)
{
  fprintf(stdout, "NanoChat shell was started.\n");

  /* --- start of shell command registeration --- */
  nc_shell_register_cmd("/help", func_cmd_help);
  nc_shell_register_cmd("/ping", func_cmd_ping);
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
	  cmds[i].func(buf);
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
nc_shell_register_cmd(char *cmd_name, void (*func)(char *cmd))
{
  cmds[cmd_current_code].code = cmd_current_code;
  cmds[cmd_current_code].func = func;
  strcpy(cmds[cmd_current_code].name, cmd_name);
  
  cmd_current_code++;
}

void
func_cmd_help(char *cmd)
{
  printf("Available commands:\n"
	 "  /help     prints this text\n"
	 "  /ping     prints pong\n"
	 "  /connect  host port\n"
	 "  /attach   room\n");
}

void
func_cmd_ping(char *cmd)
{
  printf("pong\n");
}

void
func_cmd_attach(char *cmd)
{
  int sock;
  int rc;

  rc = sscanf(cmd, "/attach %d", &sock);

  if(rc != 1) {
    printf("Error: correct format is 'attach room'.\n");
  }

  nc_log_writef("info", "Attached to room code: %d\n", sock);

  current_room_sock = sock;

  for(;;) {

    /* @TODO: multiplex shell io with select to have both read and write*/
    
    char *buf = NULL;
    int result = nn_recv(sock, &buf, NN_MSG, 0);

    if(result > 0) {
      fprintf(stdout, "<< @room-%d: %s\n", sock, buf);
    }

    nn_freemsg(buf);

  }
}

void
func_cmd_connect(char *cmd)
{
  char host[HOST_MAX];
  char port[PORT_MAX];
  char url[URL_MAX];
  int rc;  

  rc = sscanf(cmd, "connect %s %s", host, port);

  if(rc != 2) {
    printf("Error: correct format is 'connect host port'.\n");
    return;
  }

  /*
    @TODO:
    connect to discovery of remote peer node and offer
    a port number, if remote peer accepts the port, it must
    bind to that port and in response tells you it.
    then you must connect to that port.
   */
  
  strcpy(url, "tcp://");
  strcat(url, host);
  strcat(url, ":");
  strcat(url, port);
  
  printf("it will be conneted to host: %s\n",
	 url);
}
