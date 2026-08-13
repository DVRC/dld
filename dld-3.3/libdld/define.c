/* define.c -- explicitly define a named symbol.
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

/* Explicitly define the symbol named ID, of SIZE bytes. */
int
dld_define_sym (const char *id, int size)
{
  char *p = NULL;
  /* simulate a nlist entry so that _dld_entry_global_ref can be used. */
  struct nlist dummy_nlist;
  int old_undefined_sym_count;

  if (id == 0 || size == 0)
    return 0;

  if (setjmp (_dld_env)) {
    if (p != NULL)
      free (p);
    return dld_errno;
  }

  if (_dld_dummy_entry == 0)
    _dld_create_dummy_entry ();

  memset (&dummy_nlist, 0, sizeof (struct nlist));

  p = _dld_malloc (strlen (id) + 2);
  *p = '_';
  strcpy (p+1, id);

  dummy_nlist.n_un.n_name = p;
  dummy_nlist.n_type = N_UNDF | N_EXT;
  dummy_nlist.n_value = size;

  old_undefined_sym_count = dld_undefined_sym_count;
  _dld_enter_global_ref (_dld_dummy_entry, &dummy_nlist, p);

  free (p);

  if (old_undefined_sym_count != dld_undefined_sym_count) {
    _dld_patch_all_files (_dld_latest_entry);
    _dld_exec_flags_valid = 0;
  }

  return 0;
} /* dld_define_sym */
