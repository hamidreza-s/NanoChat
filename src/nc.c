#include "nc.h"

int
main(int argc, char **argv)
{
  nc_opts opts;
  nc_param_get_opts(&opts, argc, argv);
  nc_disco_start(&opts);
  sleep(1);
  nc_shell_start(&opts);

  return 0;
}
