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
  strftime(time_str, NOW_STR_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
  
}
