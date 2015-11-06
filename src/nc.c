#include "nc.h"

int
main(int argc, char **argv)
{
  nc_opts opts;
  nc_args_get_opts(&opts, argc, argv);

  printf("secure: %d\n", opts.secure);
  printf("verbose: %d\n", opts.verbose);
  printf("host: %s\n", opts.host);
  printf("port: %d\n", opts.port);
  
  return 0;
}
