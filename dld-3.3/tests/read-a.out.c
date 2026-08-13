/* add1.c -- test file to add to a global variable
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
#include "../libdld/defs.h"

#if defined(sun) && defined(sparc)
#define relocation_info reloc_info_sparc
#endif
    
int
read_a_out (int argc, char **argv)
{
  struct exec header;
  struct relocation_info relo;
  struct nlist name_list;
  FILE *objfile;
  char *string;
  int str_size;
  int i;

  if (argc < 1) {
    printf ("read-a.out: wrong number of args\n");
    return 0;
  }

  objfile = fopen (argv[1], "r");
  if (objfile == NULL) { 
    printf ("read-a.out: can't open object file\n");
    return 0;
  }

  if (!fread (&header, sizeof (header), 1, objfile)) {
    printf ("read-a.out: can't read header\n");
    return 0;
  }

#ifdef linux
  printf ("Header information:\nmagic = 0%o, text size = %ld, data size = %ld\n",
	  header.a_info, header.a_text, header.a_data);
#else
  printf ("Header information:\nmagic = 0%o, text size = %ld, data size = %ld\n",
	  header.a_magic, header.a_text, header.a_data);
#endif
  printf ("bss size = %ld, syms size = %ld, entry point = 0x%lx, trsize = %ld, drsize = %ld\n",
	  header.a_bss, header.a_syms, header.a_entry, header.a_trsize,
	  header.a_drsize);

    
  fseek (objfile, header.a_text + header.a_data + header.a_bss, 1);
  if (header.a_trsize != 0) {
    printf ("\n\nText relocation info\n");
    for (i = 0; i < (header.a_trsize / sizeof (relo)); i++) {
      fread (&relo, sizeof (relo), 1, objfile);

#if defined(sun) && defined(sparc)
      printf ("Address = 0x%lx, local offset = %d\n",
	      relo.r_address, relo.r_index);
      printf ("extern = %d, relocation type = %d, addend = %ld\n",
	      relo.r_extern, relo.r_type, relo.r_addend);
#else
	    
      printf ("Address = 0x%x, local offset = %ld\n",
	      relo.r_address, relo.r_symbolnum);
      printf ("pc relocated = %d, length = %d, extern = %d\n",
	      relo.r_pcrel, relo.r_length, relo.r_extern);
#endif	    
    }
  }

  if (header.a_drsize != 0) {
    printf ("\n\nData relocation info\n");
    for (i = 0; i < (header.a_trsize / sizeof (relo)); i++) {
      fread (&relo, sizeof (relo), 1, objfile);

#if defined(sun) && defined(sparc)
      printf ("Address = 0x%lx, local offset = %d\n",
	      relo.r_address, relo.r_index);
      printf ("extern = %d, relocation type = %d, addend = %ld\n",
	      relo.r_extern, relo.r_type, relo.r_addend);
#else
      printf ("Address = 0x%x, local offset = %d\n",
	      relo.r_address, relo.r_symbolnum);
      printf ("pc relocated = %d, length = %d, extern = %d\n",
	      relo.r_pcrel, relo.r_length, relo.r_extern);
#endif	    
    }
  }

  fseek (objfile, N_STROFF(header), 0);
  fread (&str_size, sizeof (str_size), 1, objfile);
  string = (char *) malloc (str_size);
  fseek (objfile, N_STROFF(header), 0);
  fread (string, 1, str_size, objfile);

  fseek (objfile, N_SYMOFF(header), 0);

  printf ("\n\n");
  for (i = 0; i < (header.a_syms / sizeof (struct nlist)); i++) {
    fread (&name_list, sizeof (struct nlist), 1, objfile);
    printf ("string = %s\n", string + name_list.n_un.n_strx);
    printf ("Type = 0x%x, value = 0x%08x\n",
	    name_list.n_type, (int) name_list.n_value);
  }

  return 0;
} 
