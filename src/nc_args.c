#include "nc.h"

void
nc_args_get_opts(nc_opts *opts, int argc, char **argv)
{
  int c;
  opts->verbose = 0;
  opts->secure = 0;

  while(1) {
    
    static struct option long_options[] = {
      {"verbose", no_argument, 0, 'v'},
      {"secure", no_argument, 0, 's'},
      {"help", no_argument, 0, 'h'},
      {"host", required_argument, 0, 'i'},
      {"port", required_argument, 0, 'p'},
      {0, 0, 0, 0}
    };

    int option_index = 0;

    c = getopt_long(argc, argv, "vshH:P:", long_options, &option_index);

    if(c == -1 || c == 0)
      break;

    switch(c) {

    case 'v':
      opts->verbose = 1;
      break;

    case 's':
      opts->secure = 1;
      break;

    case 'h':
      nc_util_print_help();
      exit(0);
      
    case 'H':
      if(strlen(optarg) > HOST_MAX) {
	printf("error: Host is to long!\n");
	exit(1);
      }
      strcpy(opts->host, optarg);
      break;

    case 'P':
      opts->port = strtol(optarg, NULL, 10);
      break;

    case '?':
    default:
      break;
    }
  }
}
