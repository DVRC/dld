/* remove.c -- remove an explicitly defined symbol.
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

/* Remove the explicitly defined symbol named ID. */
int
dld_remove_defined_symbol (const char *id)
{
  symbol *sp;
  char *p;
  
  if (id == 0)
    return 0;
  
  p = _dld_malloc (strlen (id) + 2);
  *p = '_';
  strcpy (p + 1, id);
  
  sp = _dld_getsym_soft (p);
  free (p);
  
  if (sp->defined_by && sp->defined_by == _dld_dummy_entry) {
    struct file_chain *p = sp->referenced_by;
    struct file_chain *prev = 0;

    while (p != 0)
      if (p->entry->ref_count == 0) {
	del_link_list_elt (sp->referenced_by, prev, p, next);
      }
      else {
	p->entry->undefined_symbol_count++;
	prev = p;
	p = p->next;
      }

    if (sp->referenced_by) {
      dld_undefined_sym_count ++;
      sp->value = 0;
    }

    if (
#ifndef linux
	sp->defined == (N_COMM | N_EXT) &&
#else
	sp->defined == (N_TYPE | N_EXT) &&
#endif
	sp->value) {
      free ((PTR) sp->value);
      sp->value = 0;
    }
    
    sp->defined = 0;
    sp->defined_by = 0;
    
    if (sp->referenced_by) {
      _dld_patch_all_files (_dld_latest_entry);
      _dld_exec_flags_valid = 0;
    }
  }
  
  return 0;
} /* dld_remove_defined_symbol */

