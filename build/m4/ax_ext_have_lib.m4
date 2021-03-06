# ===========================================================================
#      http://www.gnu.org/software/autoconf-archive/ax_ext_have_lib.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_EXT_HAVE_LIB(<directories>, <library>, <function>, <extra libraries>)
#
# DESCRIPTION
#
#   AX_EXT_HAVE_LIB is identical to AC_SEARCH_LIBS with the exception that
#   will add -L<directory> when looking, and use a different variable for
#   each directory.
#
#   Any required -L<directory> flags are added to LDFLAGS and located
#   libraies are added to LIBS
#
#   Some libraries are unlinkable without other extra libraries, which can
#   be specified in the 4th argument. The mysql client library needs -lz,
#   for example.
#
#   Example:
#
#    AX_EXT_HAVE_LIB(/lib /usr/lib /usr/local/lib /usr/lib/mysql /usr/local/mysql/lib, mysqlclient, mysql_init, [-lz], [#include <mysql.h>])
#
#   which finds the mysql client library if succeds system when it tries
#   with -L/usr/lib/mysql then it adds -lmysqlclient to LIBS and
#   -L/usr/lib/mysql to LDFLAGS.
#
#   The test itself is based on the autoconf 2.53 version of AC_SEARCH_LIBS.
#
# LICENSE
#
#   Copyright (c) 2008 Duncan Simpson <dps@simpson.demon.co.uk>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

#serial 7

AC_DEFUN([AX_EXT_HAVE_LIB],
[
new_ldflags=${LDFLAGS}
new_libs=$LIBS
ext_haslib_libvar=`echo $2 | $as_tr_sh`
eval "ext_have_${ext_haslib_libvar}"="no"

AC_CACHE_CHECK([for $2 library without parameters], [ext_cv_haslib_${ext_haslib_libvar}],
[ext_func_search_save_LIBS=$LIBS
LIBS="-l$2 $4 ${ext_func_search_save_LIBS}"
if test "x$5" = x ; then
AC_LINK_IFELSE([AC_LANG_CALL([],[$3])],
[eval "ext_cv_haslib_${ext_haslib_libvar}"="yes"],
[eval "ext_cv_haslib_${ext_haslib_libvar}"="no"])
else
AC_LINK_IFELSE([AC_LANG_PROGRAM([$5],[$3])],
[eval "ext_cv_haslib_${ext_haslib_libvar}"="yes"],
[eval "ext_cv_haslib_${ext_haslib_libvar}"="no"])
fi
LIBS=$ext_func_search_save_LIBS
])
if eval `echo 'test x${'ext_cv_haslib_${ext_haslib_libvar}'}' = "xyes"`; then
new_libs="-l$2 ${new_libs}"
eval "ext_have_${ext_haslib_libvar}"="yes"
fi

for dir in $1
do
if eval `echo 'test x${'ext_have_${ext_haslib_libvar}'}' != "xyes"`; then
ext_haslib_cvdir=`echo $dir | $as_tr_sh`
AC_CACHE_CHECK([for $2 library with -L$dir], [ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}],
[ext_func_search_save_LIBS=$LIBS
ext_func_save_ldflags=${LDFLAGS}
LIBS="-l$2 $4 ${ext_func_search_save_LIBS}"
LDFLAGS="-L$dir ${ext_func_save_ldflags}"
if test "x$5" = x ; then
AC_LINK_IFELSE([AC_LANG_CALL([],[$3])],
[eval "ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}"="yes"],
[eval "ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}"="no"])
else
AC_LINK_IFELSE([AC_LANG_PROGRAM([$5],[$3])],
[eval "ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}"="yes"],
[eval "ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}"="no"])
fi
LIBS=$ext_func_search_save_LIBS
LDFLAGS=$ext_func_save_ldflags
])
if eval `echo 'test x${'ext_cv${ext_haslib_cvdir}_haslib_${ext_haslib_libvar}'}' = "xyes"`; then
new_libs="-l$2 ${new_libs}"
new_ldflags="-L${dir} ${new_ldflags}"
eval "ext_have_${ext_haslib_libvar}"="yes"
fi
fi
done
LIBS=$new_libs
LDFLAGS=$new_ldflags
])
