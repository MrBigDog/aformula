lib_LTLIBRARIES = libaformula.la

noinst_HEADERS = jitformula.h libjitformula.h llvmformula.h muparserformula.h parser.h

libaformula_la_SOURCES = formula.cpp jitformula.cpp muparserformula.cpp parser.cpp
libaformula_la_CPPFLAGS = -I@top_srcdir@/include -I@top_srcdir@/lib/muparser
libaformula_la_LDFLAGS =

if LLVM
libaformula_la_SOURCES += llvmformula.cpp
libaformula_la_CPPFLAGS += @LLVM_CPPFLAGS@
libaformula_la_LDFLAGS += @LLVM_LDFLAGS@
endif

if LIBJIT
libaformula_la_SOURCES += libjitformula.cpp
libaformula_la_CPPFLAGS += @LIBJIT_CPPFLAGS@
libaformula_la_LDFLAGS += @LIBJIT_LDFLAGS@
endif

libaformula_la_LIBADD = @top_builddir@/lib/muparser/libmuparser.la
