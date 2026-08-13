/* error.c -- print out the error strings.
   Copyright (C) 1996 Free Software Foundation, Inc.
   Copyright (C) 1990 by W. Wilson Ho.
   This file is part of the GNU Dld Library.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* Written by W. Wilson Ho <how@sgi.com> */
#include "defs.h"

static const char *dld_errlist[] = {
  "no error",
  "cannot open file",			/* 1 DLD_ENOFILE */
  "bad magic number",			/* 2 DLD_EBADMAGIC */
  "fail to read header",		/* 3 DLD_EBADHEADER */
  "premature eof in text section",	/* 4 DLD_ENOTEXT */
  "premature eof in symbols",		/* 5 DLD_ENOSYMBOLS */
  "bad string table",			/* 6 DLD_ENOSTRINGS */
  "premature eof in text relocation",	/* 7 DLD_ENOTXTRELOC */
  "premature eof in data section",	/* 8 DLD_ENODATA */
  "premature eof in data relocation",	/* 9 DLD_ENODATRELOC */
  "multiple definitions of symbol",	/* 10 DLD_EMULTDEFS */
  "malformed library archive",		/* 11 DLD_EBADLIBRARY */
  "common block not supported",		/* 12 DLD_EBADCOMMON */
  "malformed input file",		/* 13 DLD_EBADOBJECT */
  "bad relocation info",		/* 14 DLD_EBADRELOC */
  "virtual memory exhausted",		/* 15 DLD_ENOMEMORY */
  "undefined symbol",			/* 16 DLD_EUNDEFSYM */
  "unknown error"			/* DLD_ELAST + 1 */
};

/* Print MSG followed by a colon and dld_strerror (DLD_ERRNO).  May be
   used as a simple way to report errors. */
void
dld_perror (const char *str)
{
  if (str != NULL)
    fprintf (stderr, "%s: ", str);

  if (dld_errno < 0 || dld_errno > DLD_ELAST)
    dld_errno = DLD_ELAST + 1;

  if (dld_errno == DLD_EMULTDEFS)
    fprintf (stderr, "%s: %s\n", dld_errlist[dld_errno], dld_errname);
  else
    fprintf (stderr, "%s.\n", dld_errlist[dld_errno]);
} /* dld_perror */


/* Return the string corresponding to the error code CODE. */
const char *
dld_strerror (int code)
{
  if (code < 0 || code > DLD_ELAST)
    code = DLD_ELAST + 1;

  return (dld_errlist[code]);
} /* dld_perror */
