lib_LTLIBRARIES = libaformula-@AFORMULA_API_VERSION@.la

noinst_HEADERS = codegenerator.h jitformula.h libjitformula.h llvmformula.h \
	muparserformula.h parser.h parsetree.h timer.h

libaformula_@AFORMULA_API_VERSION@_la_SOURCES = \
	benchmark.cpp formula.cpp jitformula.cpp muparserformula.cpp parser.cpp \
	timer.cpp c_api.cpp

libaformula_@AFORMULA_API_VERSION@_la_CPPFLAGS = \
	-I@top_srcdir@/include -I@top_builddir@/include -I@top_srcdir@/lib/muparser @BOOST_CPPFLAGS@

libaformula_@AFORMULA_API_VERSION@_la_LDFLAGS = -version-info @AFORMULA_SO_VERSION@ \
	@BOOST_LDFLAGS@

libaformula_@AFORMULA_API_VERSION@_la_LIBADD = \
	@top_builddir@/lib/muparser/libmuparser.la \
	@BOOST_THREAD_LIB@

if LLVM
libaformula_@AFORMULA_API_VERSION@_la_SOURCES += llvmformula.cpp
libaformula_@AFORMULA_API_VERSION@_la_CPPFLAGS += @LLVM_CPPFLAGS@
libaformula_@AFORMULA_API_VERSION@_la_LDFLAGS += @LLVM_LDFLAGS@
libaformula_@AFORMULA_API_VERSION@_la_LIBADD += @LLVM_LIBS@
endif

if LIBJIT
libaformula_@AFORMULA_API_VERSION@_la_SOURCES += libjitformula.cpp
endif
