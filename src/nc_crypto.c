#include "nc.h"

unsigned char my_publickey[crypto_box_PUBLICKEYBYTES];
unsigned char my_secretkey[crypto_box_SECRETKEYBYTES];

void
nc_crypto_start(nc_opts *opts)
{
  if(!opts->secure)
    return;

  nc_log_writef("info", "Crypto mode has been started.");
  crypto_box_keypair(my_publickey, my_secretkey);
}
