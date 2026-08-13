## Process Makefile.am with automake to create Makefile.in.
##
## Copyright (C) 1996 Free Software Foundation, Inc.
## This Makefile.am is free software; the Free Software Foundation
## gives unlimited permission to copy, distribute and modify it.
##
## Written by Gordon Matzigkeit <gord@gnu.ai.mit.edu>
# FIXME: Add ansi2knr to AUTOMAKE_OPTIONS when Automake supports multiple dirs.
AUTOMAKE_OPTIONS = gnits
TESTS = call_add1 general.test overlay reload simple
check_PROGRAMS = call_add1 general overlay \
	reload reloadme simple

# The C test programs.
call_add1_SOURCES = call_add1.c
general_SOURCES = general.c
overlay_SOURCES = overlay.c
reload_SOURCES = reload.c
simple_SOURCES = simple.c

# reloadme must be only partially linked:
reloadme: $(reloadme_OBJECTS) $(reloadme_DEPENDENCIES)
	$(CC) $(LDFLAGS) -r -o $@ $(reloadme_OBJECTS) $(reloadme_LDADD) $(LIBS)

noinst_HEADERS = overlay.h

MOSTLYCLEANFILES = test.output
CLEANFILES = general.test

# Other objects we need.
EXTRA_PROGRAMS = add1_test general_test overlay_test
add1_test_SOURCES = add1.c
general_test_SOURCES = 	hello.c print_arg.c read-a.out.c list-undefined.c \
	get-sym.c need.c test-define.c print_global.c remove.c
overlay_test_SOURCES = chain1.c chain2.c chain3.c	

EXTRA_DIST = .cvsignore SAMPLE_INPUT SAMPLE_OUTPUT general.test.in mkgentest

LIBDLD = $(top_builddir)/libdld/libdld.a
LDADD = $(LIBDLD)
CPPFLAGS = -I$(top_srcdir)

check-TESTS: $(add1_test_OBJECTS) $(general_test_OBJECTS) $(overlay_test_OBJECTS)
$(check_PROGRAMS): $(LIBDLD)
general.test: general.test.in mkgentest
	rm -f general.T
	LIBDLD="$(LIBDLD)" $(srcdir)/mkgentest $(srcdir)/general.test.in > general.T
	chmod +x general.T
	mv general.T general.test
