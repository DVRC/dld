/* get_symbol.c -- return the address of the given symbol.
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
#include "defs.h"

/* Return the address of the identifier named ID.  This function
   automatically prepends an underscore to the identifier, if C
   identifiers usually use them. */
PTR
dld_get_symbol (const char *id)
{
  char *p;
  PTR value;

  if (id == NULL)
    return NULL;

  if (setjmp (_dld_env))
    return NULL;

  /* prepend a '_' to id, as required by C's convention */
  p = _dld_malloc (strlen (id) + 2);
  *p = '_';
  strcpy (p + 1, id);

  value = dld_get_bare_symbol (p);
  free (p);
  return value;
} /* dld_get_symbol */
