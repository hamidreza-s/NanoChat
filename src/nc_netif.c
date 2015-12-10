#include "nc.h"

int
nc_netif_get_addrs(nc_netif_addrs *netif_addrs)
{
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in *sa;
  struct sockaddr_in *bc;
  
  getifaddrs(&ifap);
  for(ifa = ifap; ifa; ifa = ifa->ifa_next) {

    if(ifa->ifa_addr->sa_family == AF_INET) {

      sa = (struct sockaddr_in *) ifa->ifa_addr;
      bc = (struct sockaddr_in *) ifa->ifa_broadaddr; /* ifa->ifa_dstaddr; */ 
      
      if((strncmp(ifa->ifa_name, "en0", 3) == 0) ||
	 (strncmp(ifa->ifa_name, "eth0", 4) == 0)) {
	
	strcpy(netif_addrs->inet, inet_ntoa(sa->sin_addr));
	strcpy(netif_addrs->broadcast, inet_ntoa(bc->sin_addr));
	
	freeifaddrs(ifap);
	return 0;
      }
    }
  }

  freeifaddrs(ifap);
  return 1;
}
