#include "nc.h"

void
nc_crypto_start(nc_opts *opts)
{
  if(!opts->secure)
    return;

  nc_log_writef("info", "Crypto mode has been started.");

}
