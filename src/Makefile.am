all-local:
	mkdir -p $(top_srcdir)/var
	rm -f $(top_srcdir)/var/nanochat.conf
	echo "log_file=./var/nanochat.log" >> $(top_srcdir)/var/nanochat.conf
	touch $(top_srcdir)/var/nanochat.log

clean-local:
	rm -f $(top_srcdir)/var/nanochat.conf
	rm -f $(top_srcdir)/var/nanochat.log

AM_CFLAGS = -Wall
bin_PROGRAMS = nanochat
nanochat_SOURCES = \
	nc.h \
	nc.c \
	nc_param.c \
	nc_netif.c \
	nc_utils.c \
	nc_names.c \
	nc_udp.c \
	nc_disco.c \
	nc_rpc.c \
	nc_shell.c \
	nc_otoc.c \
	nc_conf.c \
	nc_log.c
nanochat_LDADD = $(top_srcdir)/lib/nanomsg/nanomsg-$(NANOMSG_VERSION)/lib/libnanomsg.a
nanochat_LDADD += -lpthread
nanochat_LDADD += -lanl
