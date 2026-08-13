/* list-undefined.c -- print out all the undefined symbols
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
#include <dld.h>

int
list_undefined (void)
{
  char **list = dld_list_undefined_sym ();

  if (list) {
    int i;
	    
    printf ("There are a total of %d undefined symbols:\n",
	    dld_undefined_sym_count);
    for (i = 0; i < dld_undefined_sym_count; i++)
      printf ("%d: %s\n", i+1, list[i]);
  } else
    printf ("No undefined symbols\n");

  return 0;
}
    
