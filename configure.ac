AC_PREREQ([2.69])
AC_INIT([mipea], [1.3], [44301923+jasLogic@users.noreply.github.com])
AC_CONFIG_SRCDIR([src/mipea.c])


AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])

AC_LANG(C)
AC_PROG_CC
AC_PROG_INSTALL

AM_PROG_AR
AC_PROG_RANLIB

AC_CHECK_LIB([c], [main])
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h sys/ioctl.h unistd.h])

AC_C_INLINE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_FUNC_MMAP
AC_CHECK_FUNCS([munmap])

AC_MSG_CHECKING([for /proc/cpuinfo])
if test -e "/proc/cpuinfo"
then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([cannot find file /proc/cpuinfo])
fi

AC_MSG_CHECKING([for SoC])
if test "$(grep BCM2835 /proc/cpuinfo)"
then
    AC_MSG_RESULT([BCM2835])
    AC_DEFINE([BCM2835], [1], [is a BCM2835])
else
    AC_MSG_RESULT([BCM2836/7])
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
