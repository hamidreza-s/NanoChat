#include "nc.h"

int
main(int argc, char **argv)
{
  nc_opts opts;

  /* @NOTE: conf and log must start first respectively */
  nc_conf_start();
  nc_log_start();

  nc_param_get_opts(&opts, argc, argv);

  nc_disco_start(&opts);
  nc_shell_start(&opts);

  return 0;
}
