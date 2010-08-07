#
# SYNOPSIS
#
#   AF_LIBJIT
#
# DESCRIPTION
#
#   Test for the existance of libjit, and make sure that it can be linked.
#
# LICENSE
#
#   Copyright (c) 2010  Charles Pence <charles@charlespence.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AF_LIBJIT],
[
AC_ARG_WITH([libjit],
  [AS_HELP_STRING([--with-libjit@<:@=PREFIX@:>@],
    [build with the libjit on PREFIX])],
  [],
  [with_libjit=check])

af_jit_cppflags=""
af_jit_ldflags=""

if test "x$with_libjit" != xcheck ; then
  af_jit_cppflags="-I$with_libjit/include"
  af_jit_ldflags="-L$with_libjit/lib"
  
  CPPFLAGS_SAVED="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $af_jit_cppflags"
  export CPPFLAGS
  
  LDFLAGS_SAVED="$LDFLAGS"
  LDFLAGS="$LDFLAGS $af_jit_ldflags"
  export LDFLAGS
fi

AC_CHECK_HEADERS([jit/jit.h])
AC_CHECK_LIB([jit],[jit_context_create],[found_libjit=yes],[found_libjit=no])

if test "x$with_libjit" != xcheck ; then
  CPPFLAGS="$CPPFLAGS_SAVED"
  LDFLAGS="$LDFLAGS_SAVED"
fi

AC_MSG_CHECKING([if libjit is available])
if test "x$found_libjit" = xyes -a \
        "x$ac_cv_header_jit_jit_h" = xyes ; then
  af_cv_libjit="yes"
  AC_MSG_RESULT([yes])

  AC_DEFINE([HAVE_LIBJIT],[1],[Define to 1 if the libjit library is available])
  AC_SUBST([HAVE_LIBJIT],[yes])

  AC_SUBST([LIBJIT_CPPFLAGS],[$af_jit_cppflags])
  AC_SUBST([LIBJIT_LDFLAGS],["$af_jit_ldflags -ljit"])
else
  af_cv_libjit="no"
  AC_MSG_RESULT([no])
  AC_MSG_WARN([libjit is not available; the libjit backend will not be built!])
  AC_SUBST([HAVE_LIBJIT],[no])
fi
])
