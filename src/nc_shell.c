#include "nc.h"

static nc_shell_cmd cmds[SCMD_MAX];
static int cmd_current_code = 0;
static int current_room_sock;

void func_cmd_help(char *cmd);
void func_cmd_ping(char *cmd);
void func_cmd_quit(char *cmd);
void func_cmd_connect(char *cmd);
void func_cmd_attach(char *cmd);

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
	 "  /help                prints this text\n"
	 "  /ping                prints pong\n"
	 "  /quit                quit nanochat console\n"
	 "  /connect host port   connect to remote client\n"
	 "  /attach room         attach to room\n"
	 );
}

void
func_cmd_ping(char *cmd)
{
  printf("pong\n");
}

void
func_cmd_quit(char *cmd)
{
  printf("Bye!\n");
  exit(0);
}

void
func_cmd_attach(char *cmd)
{
  int pair_raw_sock;
  int pair_fd_sock;
  int shell_fd_sock;
  int rc;

  fd_set readfds;
  int maxfds;

  char time_str[NOW_STR_LEN];

  enum {sent, received, none} last_action = none;

  rc = sscanf(cmd, "/attach %d", &pair_raw_sock);

  if(rc != 1) {
    printf("Error: correct format is 'attach room'.\n");
  }

  nc_log_writef("info", "Attached to room code: %d\n", pair_raw_sock);

  current_room_sock = pair_raw_sock;

  shell_fd_sock = 1;
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
	nc_log_writef("debug", "sent: %s", buf);
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
      fprintf(stdout, "\r[%s] <<< %s\n", time_str, buf);
      fflush(stdout);
      nc_log_writef("debug", "received: %s\n", buf);
      nn_freemsg(buf);
      last_action = received;
    }

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
