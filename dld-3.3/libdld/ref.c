/* ref.c -- explicitly make a reference to a symbol.
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

/* Explicitly create a reference to the symbol named ID. */
int
dld_create_reference (const char *id)
{
  char *p = NULL;
  struct nlist dummy_nlist;	/* simulate a nlist entry so that
				   _dld_entery_global_ref can be used. */

  if (id == NULL)
    return 0;

  if (setjmp (_dld_env)) {
    if (p) 
      free (p);
    return dld_errno;
  }

  if (_dld_dummy_entry == 0)
    _dld_create_dummy_entry ();

  memset (&dummy_nlist, 0, sizeof (struct nlist));

  p = _dld_malloc (strlen (id) +2);
  *p = '_';
  strcpy (p + 1, id);

  dummy_nlist.n_un.n_name = p;
  dummy_nlist.n_type = N_EXT | N_UNDF;

  _dld_enter_global_ref (_dld_dummy_entry, &dummy_nlist, p);

  free (p);
  return 0;
} /* dld_create_reference */
