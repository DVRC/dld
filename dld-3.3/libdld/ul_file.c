/* unlink_file.c -- unlink a given object file.
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

static struct file_entry *
search_files (struct file_entry *entry, const char *id)
{
  while (entry) {
    if (entry->library_flag) {
      struct file_entry *subentry = search_files (entry->subfiles, id);

      if (subentry != 0)
	return subentry;
    }
    else {
      if (! strcmp (entry->local_sym_name, id))
	return entry;
      if (entry->local_sym_name != entry->filename)
	if (! strcmp (entry->filename, id))
	  return entry;
    }

    entry = entry->chain;
  }
  return 0;
} /* search_files */


/* Unlink the module in the current process defined by the file FILE.
   If FORCE is nonzero, then the module is removed from memory even if
   it is referenced by other modules. */
int
dld_unlink_by_file (const char *file, int force)
{
  struct file_entry *entry = search_files (_dld_latest_entry, file);

  if (entry != NULL) {
    _dld_unlink_entry (entry, force);
    return 0;
  }

  dld_errno = DLD_EUNDEFSYM;
  return dld_errno;
} /* dld_unlink_by_file */


