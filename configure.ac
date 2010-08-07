# Initialize Autoconf, Automake
###############################
AC_INIT([aformula],[0.1],[charles@charlespence.net],[aformula],[http://wiki.github.com/cpence/aformula/])
AC_CONFIG_SRCDIR([src/formula.cpp])
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


# Libraries
###################
AX_LLVM([core jit])
AF_LIBJIT

AM_CONDITIONAL([LLVM], [test x$ax_cv_llvm = xyes])
AM_CONDITIONAL([LIBJIT], [test x$af_cv_libjit = xyes])
if test "x$ax_cv_llvm" = "xyes" ; then
  AC_SUBST([LLVM_DEF], [1])
else
  AC_SUBST([LLVM_DEF], [0])
fi
if test "x$af_cv_libjit" = "xyes" ; then
  AC_SUBST([LIBJIT_DEF], [1])
else
  AC_SUBST([LIBJIT_DEF], [0])
fi


# Output Files
##############
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
    include/Makefile
      include/aformula.h
    lib/Makefile
      lib/muparser/Makefile
        lib/muparser/tests/Makefile
    src/Makefile
    tests/Makefile
])
AC_OUTPUT


# Echo Output
#############
echo ""
echo ""
echo "AFormula Configuration:"
echo ""
echo "Available backends:"
echo "  * muParser: yes"
if test "x$ax_cv_llvm" = xyes ; then
  echo "  * LLVM: yes"
else
  echo "  * LLVM: no"
fi
if test "x$af_cv_libjit" = xyes ; then
  echo "  * libjit: yes"
else
  echo "  * libjit: no"
fi
echo ""

