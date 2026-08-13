/* list_undefined.c -- return a list of undefined symbols.
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

/* Return an array that lists the undefined symbols in the current
   process, or NULL if there are none.  The caller is responsible for
   freeing this array. */
char **
dld_list_undefined_sym (void)
{
  symbol *sp;
  int i, count;
  char **list;

  count = 0;
  if (dld_undefined_sym_count == 0)
    return NULL;

  if (setjmp (_dld_env))
    return 0;

  list = _dld_malloc (sizeof (char *) * dld_undefined_sym_count);

  for (i = 0; i < TABSIZE; i++)
    for (sp = _dld_symtab[i]; sp != NULL; sp = sp->link)
      if (!sp->defined) {
	list[count++] = sp->name;
	if (count >= dld_undefined_sym_count)
	  break;
      }

  return list;
} /* dld_list_undefined_sym */

