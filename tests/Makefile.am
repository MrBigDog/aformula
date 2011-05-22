AM_DEFAULT_SOURCE_EXT = .cpp
AM_CPPFLAGS = -I@top_srcdir@/include @BOOST_CPPFLAGS@
AM_LDFLAGS = @BOOST_LDFLAGS@

check_PROGRAMS = test1 test2 test3 test4
TESTS = $(check_PROGRAMS)

test1_SOURCES = test1.cpp
test1_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la
test2_SOURCES = test2.cpp
test2_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la
test3_SOURCES = test3.cpp
test3_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la
test4_SOURCES = test4.c
test4_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la
