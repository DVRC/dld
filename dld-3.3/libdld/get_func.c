/* get_func.c -- Return the entry point of the given function.
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

/* Return the address of the function named FUNC. */
PTR
dld_get_func (const char *func)
{
  symbol *sp;
  char *p;

  if (func == NULL)
    return NULL;

  if (setjmp (_dld_env))
    return NULL;

  /* prepend a '_' to func, as required by C's convention */
  p = _dld_malloc (strlen (func) + 2);
  *p = '_';
  strcpy (p + 1, func);

  sp = _dld_getsym_soft (p);
  free (p);

#ifdef linux
  if (sp) {
    while (sp->indirect)
      sp = sp->indirect;
    if ((sp->defined == (N_EXT | N_TEXT)) || (sp->defined == (N_EXT | N_ABS)))
      return sp->value;
  }
#else
  if (sp)
    if (sp->defined == (N_EXT | N_TEXT))
      return sp->value;
#endif
  return 0;
} /* dld_get_func */


