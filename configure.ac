# Initialize Autoconf, Automake
###############################
AC_INIT([aformula],[0.1],[charles@charlespence.net],[aformula],[http://wiki.github.com/cpence/aformula/])
AC_CONFIG_SRCDIR([src/aformula.cpp])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build/m4])

AM_INIT_AUTOMAKE([-Wall -Werror gnits 1.9.6])


# Program Tests
###############
AM_PROG_CC_C_O
AC_PROG_CXX

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_AWK

LT_PREREQ([2.2.10])
LT_INIT([disable-shared])
AC_SUBST([LIBTOOL_DEPS])


# C++ Feature Tests
###################
AC_LANG(C++)


# Output Files
##############
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
    lib/Makefile
      lib/muparser/Makefile
        lib/muparser/tests/Makefile
    src/Makefile
])
AC_OUTPUT

