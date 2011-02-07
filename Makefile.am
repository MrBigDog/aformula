ACLOCAL_AMFLAGS = -I build/m4

SUBDIRS = include lib src tests

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

include build/doxygen.inc
MOSTLYCLEANFILES = $(DX_CLEANFILES)
EXTRA_DIST = $(DX_CONFIG)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = aformula-$(AFORMULA_API_VERSION).pc

changes:
	$(top_srcdir)/build/gitlog2changelog.py

docs:
	$(SHELL) ./config.status include/aformula.h
	rm -f $(top_srcdir)/doc/aformula.tag
	$(MAKE) doxygen-doc
