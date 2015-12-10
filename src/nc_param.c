#include "nc.h"

void
nc_param_get_opts(nc_opts *opts, int argc, char **argv)
{
  int c;
  int rc;
  
  opts->host[0] = '\0';
  opts->broadcast[0] = '\0';
  opts->port[0] = '\0';
  opts->url[0] = '\0';
  opts->verbose = 0;
  opts->secure = 0;
  
  for(;;) {
    
    static struct option long_options[] = {
      {"verbose", no_argument, 0, 'v'},
      {"secure", no_argument, 0, 's'},
      {"help", no_argument, 0, 'h'},
      {"host", required_argument, 0, 'H'},
      {"broadcast", required_argument, 0, 'B'},
      {"port", required_argument, 0, 'P'},
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
      nc_utils_print_help();
      exit(0);
      
    case 'H':
      if(strlen(optarg) >= HOST_MAX) {
	fprintf(stderr, "Error: Host is to long!\n");
	exit(1);
      }
      strcpy(opts->host, optarg);
      break;

    case 'B':
      if(strlen(optarg) >= HOST_MAX) {
	fprintf(stderr, "Error: Broadcast is to long!\n");
	exit(1);
      }
      strcpy(opts->broadcast, optarg);
      break;
      
    case 'P':
      if(strlen(optarg) >= PORT_MAX) {
	fprintf(stderr, "Error: Port can not be more than 5 character!\n");
	exit(1);
      }
      strcpy(opts->port, optarg);
      break;

    case '?':
    default:
      break;
    }
  }

  if(opts->host[0] == '\0' || opts->broadcast[0] == '\0') {

    rc = nc_netif_get_addrs(opts->host, opts->broadcast);
    if(rc != 0) {
      fprintf(stderr, "Error: no network interface was found!");
      exit(0);
    }

  }

  if(opts->port[0] == '\0') {
    strcpy(opts->port, DEFAULT_RPC_PORT);
  }

  nc_utils_make_url(opts->url, opts->host, opts->port);
}

