SUBDIRS = . tests

noinst_LTLIBRARIES = libmuparser.la

libmuparser_la_CFLAGS = -I$(srcdir)

libmuparser_la_SOURCES = muParser.cpp muParserBase.cpp muParserBytecode.cpp \
	muParserCallback.cpp muParserDLL.cpp muParserError.cpp muParserTest.cpp \
	muParserTokenReader.cpp

noinst_HEADERS = muParser.h muParserBase.h muParserBytecode.h muParserCallback.h \
	muParserDLL.h muParserDef.h muParserError.h muParserFixes.h muParserStack.h \
	muParserTest.h muParserToken.h muParserTokenReader.h


