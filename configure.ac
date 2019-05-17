AC_PREREQ([2.69])
AC_INIT([mipea], [2.0.0])
AC_CONFIG_SRCDIR([src/mipea.c])


AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])

AC_LANG(C)
AC_PROG_CC
AC_PROG_INSTALL

AM_PROG_AR
LT_INIT

AC_CHECK_LIB([c], [main], [], [AC_MSG_ERROR([libc is needed])])
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h sys/ioctl.h unistd.h], [], [AC_MSG_ERROR([header missing])])

AC_C_INLINE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_FUNC_MMAP
AC_CHECK_FUNCS([munmap])

# check for the cpuinfo file -> needed to find out SoC and Revision
AC_MSG_CHECKING([for /proc/cpuinfo])
if test -e "/proc/cpuinfo"
then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([cannot find file /proc/cpuinfo])
fi

# check the SoC
AC_MSG_CHECKING([for SoC])
if test "$(grep BCM2835 /proc/cpuinfo)"
then
    AC_MSG_RESULT([BCM2835])
    AC_DEFINE([BCM2835], [1], [Define to 1 if the SoC is a BCM2835])
else
    AC_MSG_RESULT([BCM2836/7])
    AC_DEFINE([BCM2836_7], [1], [Define to 1 if the SoC is a BCM2836/7])
fi

# check if it is a "old" pi -> rev < 0004 -> then use bus 0
AC_MSG_CHECKING([for I2C bus])
rev="$(grep Revision /proc/cpuinfo)"
if test "${rev: -4}" -lt "4"
then
    AC_MSG_RESULT([0])
    AC_DEFINE([USE_I2C_BUS_0], [1], [Define to 1 if the SoC uses I2C bus 0 (Revision < 0004)])
else
    AC_MSG_RESULT([1])
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
