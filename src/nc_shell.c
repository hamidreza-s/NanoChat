#include "nc.h"

static nc_shell_cmd cmds[SCMD_MAX];
static int cmd_current_code = 0;

void func_cmd_help(void);
void func_cmd_ping(void);

void
nc_shell_start(nc_opts *opts)
{
  fprintf(stdout, "NanoChat shell was started.\n");

  /* --- start of shell command registeration --- */
  nc_shell_register_cmd("help", func_cmd_help);
  nc_shell_register_cmd("ping", func_cmd_ping);
  /* --- end of shell command registration --- */
  
  for(;;) {
    
    char *buf = NULL;
    size_t buf_size = 1024;
    int i;
    int found;

    found = 0;
    fprintf(stdout, ">> ");
    getline(&buf, &buf_size, stdin);

    for(i = 0; i < SCMD_MAX; i++) {

      nc_utils_del_new_line(buf);
      
      if(!strcmp(buf, cmds[i].name)) {
	cmds[i].func();
	found = 1;
	break;
      }
      
    }

    if(!found)
      printf("Command not found!\n"
	     "Type 'help' to list available commands.\n");
    
  }
}

void
nc_shell_register_cmd(char *cmd_name, void (*func)(void))
{
  cmds[cmd_current_code].code = cmd_current_code;
  cmds[cmd_current_code].func = func;
  strcpy(cmds[cmd_current_code].name, cmd_name);

  cmd_current_code++;
}

void
func_cmd_help(void)
{
  printf("Available commands:\n"
	 "  help     prints this text\n"
	 "  ping     prints pong\n");
}

void
func_cmd_ping(void)
{
  printf("pong\n");
}
