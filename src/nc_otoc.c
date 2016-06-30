#include "nc.h"

static nc_otoc_cmd cmds[OCMD_MAX];
static int cmd_current_code = 0;

static int func_cmd_help(char *cmd);
static int func_cmd_leave(char *cmd);

void
nc_otoc_start(nc_opts *opts, int pair_raw_sock)
{
  int shell_fd_sock;
  int pair_fd_sock;

  fd_set readfds;
  int maxfds;
  char time_str[NOW_STR_LEN];

  enum {init, none,
	text_sent, text_received,
	pkey_sent, pkey_received} last_action = init;

  shell_fd_sock = fileno(stdin);
  pair_fd_sock = nc_utils_get_rec_sockfd(pair_raw_sock);
  maxfds = pair_fd_sock + 1;

  /* --- start of sending public key --- */
  if(opts->secure) {

    char *msg = NULL;
    char *msg_type = OTOC_MTYPE_PKEY;
    char *msg_body = NULL;

    /* --- start of encoding public key --- */
    const char *plain_pkey = (const char*) my_publickey;
    int plain_pkey_len = crypto_box_PUBLICKEYBYTES;
    char encoded_pkey[Base64encode_len(plain_pkey_len)];
    Base64encode(encoded_pkey, plain_pkey, strlen(plain_pkey));
    nc_log_writef("debug", "encode my public key: %s", encoded_pkey);
    /* --- end of encoding public key --- */

    msg_body = encoded_pkey;
    nc_json_make_otoc_msg(&msg_type, &msg_body, &msg);
    nn_send(pair_raw_sock, msg, strlen(msg), 0);
    nc_log_writef("debug", "one to one chat sent public key: %s", msg);
    last_action = pkey_sent;
    
  }
  /* --- end of sending public key --- */
  
  /* --- start of shel command registration --- */
  nc_otoc_register_cmd("/help", func_cmd_help);
  nc_otoc_register_cmd("/leave", func_cmd_leave);
  /* --- end of shell commmand registration --- */

  for(;;) {

    switch(last_action) {
    case init:
    case pkey_sent:
      fprintf(stdout,
	      ">> Entering (room code %d) ...\n",
	      pair_raw_sock);
      fprintf(stdout, ">>> ");
      fflush(stdout); 
      break;
    case text_received: 
      fprintf(stdout, ">>> ");
      fflush(stdout); 
      break;
    case text_sent: 
      fprintf(stdout, ">>> "); 
      fflush(stdout); 
      break;
    case none:
      fprintf(stdout, ">>> ");
      fflush(stdout);
      break;
    case pkey_received:
      break;
    }

    FD_ZERO(&readfds);
    FD_SET(pair_fd_sock, &readfds);
    FD_SET(shell_fd_sock, &readfds);

    select(maxfds, &readfds, NULL, NULL, NULL);

    if(FD_ISSET(shell_fd_sock, &readfds)) {      

      char *buf = NULL;
      size_t buf_sz = 1024;
      int i;

      nc_utils_now_str(time_str);      
      getline(&buf, &buf_sz, stdin);

      if(buf[0] == '\n') {
	
	last_action = none;

      } else if(buf[0] == '/') {

	nc_utils_del_new_line(buf);
	for(i = 0; i < cmd_current_code; i++) {
	  
	  if(strstr(buf, cmds[i].name)) {

	    if(cmds[i].func(buf) < 0) {
	      return;
	    }

	    break;
	  }
	}

	last_action = none;

      } else {

	char *msg = NULL;
	char *msg_type = OTOC_MTYPE_RTXT;
	nc_json_make_otoc_msg(&msg_type, &buf, &msg);
	nn_send(pair_raw_sock, msg, strlen(msg), 0);
	fprintf(stdout, "[%s] >>> %s", time_str, buf);
	fflush(stdout);
	nc_utils_del_new_line(buf);
	nc_log_writef("debug", "one to one chat sent: %s", buf);
	nc_utils_empty_string(buf);
	last_action = text_sent;
      }
      
    } else if(FD_ISSET(pair_fd_sock, &readfds)) {

      /* @TODO: if both peers are not in same security mode */
      
      char *buf = NULL;
      char *msg_body = NULL;
      char *msg_type = NULL;
      
      nn_recv(pair_raw_sock, &buf, NN_MSG, 0);
      nc_json_extract_otoc_msg(&buf, &msg_type, &msg_body);
      nc_utils_del_new_line(buf);
      nc_log_writef("debug", "one to one chat received: %s", buf);
      nn_freemsg(buf);
      
      if(strncmp(msg_type, OTOC_MTYPE_PKEY, OTOC_MTYPE_LEN) == 0) {

	/* public key message */

	/* --- start of decoding public key --- */
	int plain_pkey_len = Base64decode_len(msg_body);
	char plain_pkey[plain_pkey_len];
	Base64decode(plain_pkey, (const char*) msg_body);
	strncpy(peers_publickey[pair_raw_sock], plain_pkey, crypto_box_PUBLICKEYBYTES);
	nc_log_writef("debug", "decoded peer's public key was stored.");
	/* --- end of decoding public key --- */
	
	last_action = pkey_received;
	
      } else if(strncmp(msg_type, OTOC_MTYPE_RTXT, OTOC_MTYPE_LEN) == 0) {

	/* raw text messagee */

	nc_utils_now_str(time_str);
	fprintf(stdout, "\r[%s] <<< %s", time_str, msg_body);
	fflush(stdout);
	last_action = text_received;

      }
    }
    
  }

}

void
nc_otoc_register_cmd(char *cmd_name, int (*func)(char *cmd))
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
	 "  /leave               leave current room\n"
	 );
  return 0;
}

int
func_cmd_leave(char *cmd)
{
  printf("leaving room ...\n");
  return -1;
}
