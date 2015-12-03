#include "nc.h"

void
nc_utils_print_help()
{
  fprintf(stdout,
	  "NanoChat help\n"
	  "-------------\n"
	  "Avaliable flags:\n"
	  "    Help:       -h --help\n"
	  "    Host:       -H --host\n"
	  "    Port:       -P --port\n"
	  "    Verbose:    -v --verbose\n"
	  "    Secure:     -s --secure\n"
	  );
}

int
nc_utils_count_char(const char *str, const char chr)
{
  char *chr_ptr;
  int count;

  count = 0;
  chr_ptr = strchr(str, chr);
  
  while(chr_ptr != NULL) {
    ++count;
    chr_ptr = strchr(chr_ptr + 1, chr);
  };

  return count;
}

void
nc_utils_now_str(char *time_str)
{
  time_t now;

  time(&now);
  strftime(time_str, NOW_STR_LEN, "%Y-%m-%d %H:%M:%S",
	   localtime(&now));  
}

void
nc_utils_del_new_line(char *str)
{
  char *new_line;
  
  if((new_line = strchr(str, '\n')) != NULL) {
    *new_line = '\0';
  }
}

int
nc_utils_has_new_line(char *str)
{
  char *new_line = NULL;

  if((new_line = strchr(str, '\n')) == NULL) {
    return 0;
  }

  return 1;
}

void
nc_utils_make_url(char *url, char *host, char *port)
{
  url[0] = '\0';
  strcat(url, "tcp://");
  strcat(url, host);
  strcat(url, ":");
  strcat(url, port);
}

int
nc_utils_get_rec_sockfd(int sock)
{
  int rcvfd;
  size_t rcvfd_sz = sizeof(rcvfd);
  nn_getsockopt(sock, NN_SOL_SOCKET, NN_RCVFD, &rcvfd, &rcvfd_sz);
  return rcvfd;
}

void
nc_utils_empty_string(char *str)
{
  memset(str, '\0', strlen(str));
}

void
nc_utils_die(char *str)
{
  perror(str);
  exit(1);
}

