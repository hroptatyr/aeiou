### Makefile.am
include $(top_builddir)/version.mk

AM_CFLAGS = $(EXTRA_CFLAGS)
AM_CPPFLAGS = -D_POSIX_C_SOURCE=201001L -D_XOPEN_SOURCE=700 -D_BSD_SOURCE
AM_CPPFLAGS += -D_HAVE_VERSION_H
AM_LDFLAGS = $(XCCLDFLAGS)

bin_PROGRAMS =
noinst_PROGRAMS =
noinst_HEADERS =
pkgdata_DATA =
BUILT_SOURCES =
EXTRA_DIST = $(BUILT_SOURCES)
CLEANFILES = 
SUFFIXES =

CLEANFILES += version.c
EXTRA_DIST += version.c.in
EXTRA_DIST += nifty.h

bin_PROGRAMS += aeiou
aeiou_SOURCES = aeiou.c aeiou.yuck
aeiou_SOURCES += version.c version.h
BUILT_SOURCES += aeiou.yucc

bin_PROGRAMS += translit
translit_SOURCES = translit.c translit.yuck
translit_SOURCES += version.c version.h
EXTRA_translit_SOURCES = unidecode_tr.c
BUILT_SOURCES += translit.yucc

pkgdata_DATA += tr_639_1_de.tr
pkgdata_DATA += tr_639_1_ru.tr

## version rules
version.c: version.c.in $(top_builddir)/.version
	$(AM_V_GEN) PATH="$(top_builddir)/build-aux:$${PATH}" \
		yuck$(EXEEXT) scmver --ignore-noscm --force -o $@ \
			--use-reference --reference $(top_builddir)/.version $<

## yuck rule
SUFFIXES += .yuck
SUFFIXES += .yucc
.yuck.yucc:
	$(AM_V_GEN) PATH=$(top_builddir)/build-aux:"$${PATH}" \
		yuck$(EXEEXT) gen -o $@ $<

## tr rule
SUFFIXES += .tr
.c.tr:
	$(AM_V_GEN) $(COMPILE) -DTRFILE='"$<"' $(srcdir)/translcc.c -o tr.out && \
		./tr.out > $@
	$(RM) tr.out

## Create preprocessor output (debugging purposes only)
.c.i:
	$(COMPILE) -E -o $@ $<

## Create assembler output (debugging purposes only)
.c.s:
	$(COMPILE) -S -c $(AM_CFLAGS) $<
