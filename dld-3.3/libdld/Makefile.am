## Process Makefile.am with automake to create Makefile.in.
##
## Copyright (C) 1996 Free Software Foundation, Inc.
## This Makefile.am is free software; the Free Software Foundation
## gives unlimited permission to copy, distribute and modify it.
##
## Written by Gordon Matzigkeit <gord@gnu.ai.mit.edu>
AUTOMAKE_OPTIONS = ansi2knr gnits
lib_LIBRARIES = dld
dld_SOURCES = define.c dld.c error.c find_exec.c get_func.c get_symbol.c \
	list_undef.c mk_dummy.c ref.c ul_file.c ul_symbol.c remove.c \
	@LIBOBJS@

noinst_HEADERS = defs.h
CPPFLAGS = -I$(top_srcdir)

EXTRA_DIST = .cvsignore
