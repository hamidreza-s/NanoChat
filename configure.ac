AC_PREREQ([2.69])
AC_INIT([nanochat], [0.1], [hamidreza.s@gmail.com])
AM_INIT_AUTOMAKE([foreign])

NANOMSG_VERSION=0.8-beta
AC_SUBST([NANOMSG_VERSION])

AC_PROG_CC
AC_LANG([C])

AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h unistd.h getopt.h string.h time.h \
			  sys/select.h stdarg.h pthread.h pwd.h sys/socket.h \
			  arpa/inet.h ifaddrs.h])

AC_TYPE_SIZE_T
AC_CONFIG_FILES([Makefile lib/nanomsg/Makefile src/Makefile])

AC_OUTPUT
