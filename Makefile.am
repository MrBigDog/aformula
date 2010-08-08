ACLOCAL_AMFLAGS = -I build/m4

SUBDIRS = include lib src tests

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

include build/doxygen.am
MOSTLYCLEANFILES = $(DX_CLEANFILES)
EXTRA_DIST = $(DX_CONFIG)

changes:
	$(top_srcdir)/build/gitlog2changelog.py


