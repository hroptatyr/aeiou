# Help the Developers and yourself. Just use the C locale and settings
# for the compilation. They can still be overriden by make LANG=<whatever>
# but that is general a not very good idea
include $(top_builddir)/version.mk

LANG = C
LC_ALL = C

AM_CFLAGS = $(EXTRA_CFLAGS)
AM_CPPFLAGS = -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 -D_BSD_SOURCE
AM_CPPFLAGS += -DTEST

EXTRA_DIST = $(BUILT_SOURCES) $(TESTS)
TESTS =
TEST_EXTENSIONS =
BUILT_SOURCES =
dt_tests =
bin_tests =
batch_tests =
check_PROGRAMS =
CLEANFILES = $(check_PROGRAMS)

## summon our helper
include clitoris.am
AM_CLIT_LOG_FLAGS = -v --builddir $(top_builddir)/src
TESTS_ENVIRONMENT = root=$(top_srcdir) AEIOU_TRPATH=$(TRDIR)


## transliteration files used in the tests
TRDIR_FILES =
TRDIR_FILES += tr_639_1_de.tr
TRDIR_FILES += tr_639_1_ja.tr
TRDIR_FILES += tr_639_1_ru.tr
TRDIR = $(builddir)

## examples from README
TESTS += readme_test_01.clit
TESTS += readme_test_02.clit
TESTS += readme_test_03.clit
TESTS += readme_test_04.clit
TESTS += readme_test_05.clit


## relocate all trdir files here
VPATH += $(top_builddir)/src:$(top_srcdir)/src
check: check_TRDIR_FILES
check_TRDIR_FILES: $(TRDIR_FILES)
	-$(LN_S) $^ $(TRDIR)

DISTCLEANFILES = $(TRDIR_FILES)

## Makefile.am ends here
