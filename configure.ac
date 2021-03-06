# Initialize Autoconf, Automake
###############################
AC_INIT([aformula],[0.9.6],[charles@charlespence.net],[aformula],[http://cpence.github.com/aformula/])
AC_CONFIG_SRCDIR([src/formula.cpp])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build/m4])

AM_INIT_AUTOMAKE([-Wall -Werror gnits 1.9.6 dist-bzip2])

LT_PREREQ([2.2.4])
AM_PROG_AR
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

AC_SUBST([AFORMULA_SO_VERSION], [2:3:0])
AC_SUBST([AFORMULA_API_VERSION], [1.1])


# Program Tests
###############
AC_PROG_CXX

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_AWK


# C++ Feature Tests
###################
AC_LANG(C++)
AX_CXXFLAGS_WARN_ALL


# Libraries
###################
AC_CHECK_HEADERS([sys/types.h sys/wait.h])
AC_CHECK_HEADERS([unistd.h],[],[AC_MSG_ERROR([unistd.h not found: if using Win32, compile under Cygwin!])])

AX_BOOST_BASE([1.29.0])
AX_BOOST_THREAD

AX_EXT_HAVE_HEADER([jit/jit.h], [/include /usr/include /usr/local/include /opt/include /opt/local/include])
AX_EXT_HAVE_LIB([/lib /usr/lib /usr/local/lib /opt/lib /opt/local/lib /usr/lib/x86 /usr/lib/x86_64 /usr/local/lib/x86 /usr/local/lib/x86_64 /opt/lib/x86 /opt/lib/x86_64 /opt/local/lib/x86 /opt/local/lib/x86_64], [jit], [jit_context_create])
if test "x$ext_cv_jit_jit_h" = "xyes" -a "x$ext_have_jit" = "xyes" ; then
  AC_DEFINE([HAVE_LIBJIT],[1],[Define to 1 if the libjit library is available])
  AC_SUBST([HAVE_LIBJIT],[yes])
  have_libjit="yes"
else
  AC_MSG_WARN([libjit is not available; the libjit backend will not be built!])
  AC_SUBST([HAVE_LIBJIT],[no])
  have_libjit="no"
fi

AX_LLVM([core engine native ipo])
if test "x$ax_cv_llvm" = "xyes" ; then
  AC_DEFINE([HAVE_LLVM],[1],[Define to 1 if the LLVM library is available])
  AC_SUBST([HAVE_LLVM],[yes])
  have_llvm="yes"
else
  AC_MSG_WARN([LLVM is not available; the LLVM backend will not be built!])
  AC_SUBST([HAVE_LLVM],[no])
  have_llvm="no"
fi

AM_CONDITIONAL([LLVM], [test x$have_llvm = xyes])
AM_CONDITIONAL([LIBJIT], [test x$have_libjit = xyes])
if test "x$have_llvm" = "xyes" ; then
  AC_SUBST([LLVM_DEF], [1])
else
  AC_SUBST([LLVM_DEF], [0])
fi
if test "x$have_libjit" = "xyes" ; then
  AC_SUBST([LIBJIT_DEF], [1])
else
  AC_SUBST([LIBJIT_DEF], [0])
fi


# Doxygen documentation
#######################

DX_HTML_FEATURE([ON])
DX_CHM_FEATURE([OFF])
DX_CHI_FEATURE([OFF])
DX_MAN_FEATURE([OFF])
DX_RTF_FEATURE([OFF])
DX_XML_FEATURE([OFF])
DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([aformula], [doxygen.cfg], [doc])


# Output Files
##############
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  aformula-1.1.pc
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
if test "x$have_llvm" = xyes ; then
  echo "  * LLVM: yes"
else
  echo "  * LLVM: no"
fi
if test "x$have_libjit" = xyes ; then
  echo "  * libjit: yes"
else
  echo "  * libjit: no"
fi
echo ""

