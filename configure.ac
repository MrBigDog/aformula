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


# Libraries
###################
AX_LLVM([core jit])

AC_CHECK_HEADERS([jit/jit.h])
AC_CHECK_LIB([jit],[jit_context_create],[],[])
AC_MSG_CHECKING([if libjit is available])
if test "x$ac_cv_lib_jit_jit_context_create" = xyes -a \
        "x$ac_cv_header_jit_jit_h" = xyes ; then
  af_have_libjit="yes"
  AC_MSG_RESULT([yes])
  AC_DEFINE([HAVE_LIBJIT],[1])
  AC_SUBST([HAVE_LIBJIT],[yes])
  AC_SUBST([JIT_CPPFLAGS],[])
  AC_SUBST([JIT_LDFLAGS],[-ljit])
else
  af_have_libjit="no"
  AC_MSG_RESULT([no])
  AC_MSG_WARN([libjit is not available; the libjit backend will not be built!])
  AC_SUBST([HAVE_LIBJIT],[no])
fi


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
if test "x$af_have_libjit" = xyes ; then
  echo "  * libjit: yes"
else
  echo "  * libjit: no"
fi
echo ""

