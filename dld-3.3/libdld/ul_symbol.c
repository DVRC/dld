/* unlink_symbol.c -- unlink the object file defining the given symbol.
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

/* Unlink the module in the current process that defines the symbol
   ID.  If FORCE is nonzero, then the module is removed from memory
   even if it is referenced by other modules. */
int
dld_unlink_by_symbol (const char *id, int force)
{
  symbol *sp;
  char *p;

  if (id == 0) {
    dld_errno = DLD_EUNDEFSYM;
    return dld_errno;
  }

  if (setjmp (_dld_env))
    return dld_errno;

  /* prepend a '_' to id, as required by C's convention */
  p = (char *) _dld_malloc (strlen (id) + 2);
  *p = '_';
  strcpy (p + 1, id);

  sp = _dld_getsym_soft (p);
  free (p);

  if (sp && sp->defined_by) {
    if (sp->defined_by != _dld_dummy_entry)
      _dld_unlink_entry (sp->defined_by, force);
    else dld_remove_defined_symbol (id);

    return 0;
  }

  dld_errno = DLD_EUNDEFSYM;
  return dld_errno;
} /* dld_unlink_by_symbol */


