AM_CPPFLAGS = -I@top_srcdir@/include -I@top_srcdir@/lib/muparser @LLVM_CPPFLAGS@ @JIT_CPPFLAGS@
AM_LDFLAGS = @LLVM_LDFLAGS@ @JIT_LDFLAGS@

lib_LTLIBRARIES = libaformula.la

noinst_HEADERS = \
	jitformula.h muparserformula.h parser.h

libaformula_la_SOURCES = \
	formula.cpp jitformula.cpp muparserformula.cpp parser.cpp

libaformula_la_LIBADD = @top_builddir@/lib/muparser/libmuparser.la
