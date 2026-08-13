/* need.c -- explicitly reference the given symbol, so that the library
             routine defining this symbol will be loaded
   Copyright (C) 1996 Free Software Foundation, Inc.
   Copyright (C) 1990 W. Wilson Ho
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
#include <stdio.h>
#include <dld.h>

int
need (int argc, char **argv)
{
  int i;

  for (i = 1; i < argc; i++) {
    int dld_errno;
	
    printf ("%d: %s", i, argv[i]);
    fflush (stdout);
    dld_errno = dld_create_reference (argv[i]);
    if (dld_errno)
      printf ("need: error: %d\n", dld_errno);
    else {
      if (dld_get_symbol (argv[i]))
	printf ("need: symbol \"%s\" already defined\n", argv[i]);
      else printf ("\n");
    }
  }
  return 0;
}
