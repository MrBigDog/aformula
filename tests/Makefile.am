AM_DEFAULT_SOURCE_EXT = .cpp
AM_CPPFLAGS = -I@top_srcdir@/include @BOOST_CPPFLAGS@
AM_LDFLAGS = @BOOST_LDFLAGS@

check_PROGRAMS = test1 test2
TESTS = $(check_PROGRAMS)

test1_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la
test2_LDADD = @top_builddir@/src/libaformula-$(AFORMULA_API_VERSION).la

