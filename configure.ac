AC_PREREQ([2.69])
AC_INIT([nanochat], [0.1], [hamidreza.s@gmail.com])
AM_INIT_AUTOMAKE([foreign])

NANOMSG_VERSION=0.8-beta
AC_SUBST([NANOMSG_VERSION])

VEDIS_VERSION=1.2.6
AC_SUBST([VEDIS_VERSION])

AC_PROG_CC
AC_LANG([C])

AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h unistd.h getopt.h string.h time.h \
			  sys/select.h stdarg.h pthread.h pwd.h sys/socket.h \
			  arpa/inet.h ifaddrs.h])

AC_TYPE_SIZE_T
AC_CONFIG_FILES([Makefile lib/nanomsg/Makefile lib/vedis/Makefile src/Makefile])

AC_CANONICAL_HOST
case "${host_os}" in
    *linux*)
        # Define on Linux to enable all library features
	NC_OS_SPECIFIC_LDADD="-l:libnanomsg.a -l:libvedis.a"
	NC_EXTRA_LDADD=-lanl 
        ;;
    *freebsd*)
        # Define on FreeBSD to enable all library features
	NC_OS_SPECIFIC_LDADD="-lnanomsg -lvedis"
	NC_EXTRA_LDADD=
        ;;
    *darwin*)
        # Define on Darwin to enable all library features
	NC_OS_SPECIFIC_LDADD="-lnanomsg -lvedis"
	NC_EXTRA_LDADD=
        ;;
    *)
        AC_MSG_ERROR([unsupported system: ${host_os}.])
        ;;
esac
AC_SUBST([NC_OS_SPECIFIC_LDADD])
AC_SUBST([NC_EXTRA_LDADD])

AC_OUTPUT
