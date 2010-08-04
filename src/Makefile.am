AM_CPPFLAGS = -I@top_srcdir@/include -I@top_srcdir@/lib/muparser @LLVM_CPPFLAGS@ @JIT_CPPFLAGS@
AM_LDFLAGS = @LLVM_LDFLAGS@ @JIT_LDFLAGS@

lib_LTLIBRARIES = libaformula.la

libaformula_la_SOURCES = formula.cpp muparserformula.cpp

libaformula_la_LTADD = @top_builddir@/lib/muparser/libmuparser.la
