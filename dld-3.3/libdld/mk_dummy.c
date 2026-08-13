/* mk_dummy.c -- create a dummy file_entry for explicit symbols.
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

void
_dld_create_dummy_entry (void)
{

  struct file_entry *entry;

  if (_dld_dummy_entry)
    return;

  entry = _dld_malloc (sizeof (struct file_entry));

  memset (entry, 0, sizeof (struct file_entry));
  entry->filename = entry->local_sym_name = "-*- dummy entry -*-";
  entry->chain = _dld_latest_entry;
  _dld_latest_entry = entry;
  entry->ref_count = 1;
  _dld_dummy_entry = entry;

  return;
} /* _dld_create_dummy_entry */
