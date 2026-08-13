/* reload.c -- unlink the "main" module and load in another one
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
#include <stdio.h>
#include <dld.h>

#define RELOADME "reloadme"

char foo, bar;
char *newargv[] = {
  &bar,
  &bar
};

int
main (int argc, char **argv)
{
  int (*func) (int, char **);
  int *new_brk;
  
  if (dld_init(argv[0]) != 0) {
    dld_perror ("dld_init");
    return 1;
  }
  
  /* Unlink ourself. */
  if (dld_unlink_by_file (dld_find_executable (argv[0]), 1) != 0) {
    dld_perror ("dld_unlink_by_file");
    return 1;
  }
  
  if (dld_link (RELOADME) != 0) {
    dld_perror ("dld_link");
    return 1;
  }

#if 0
  /* FIXME: dld_function_executable_p gives a false negative. */
  if (! dld_function_executable_p ("main")) {
    fprintf (stderr, "%s: function main in %s is not executable\n",
	     argv[0], RELOADME);
    return 1;
  }
#endif

  func = (int (*) (int, char **)) dld_get_func ("main");
  if (func == 0) {
    dld_perror ("dld_get_func");
    return 1;
  }

#ifndef sequent
  /* "curbrk" is a symbol used by sbrk(2) to record the current
     break of the process.  It is initialized to the address of
     "_end". Since we are loading in a new copy of sbrk, we must
     set its value to the true current break of the process.
     Otherwise, the first call to the new sbrk will get a seg. fault */
# ifdef linux
  new_brk = (int *) dld_get_bare_symbol ("____brk_addr");
# else
  new_brk = (int *) dld_get_bare_symbol ("curbrk");
# endif
  if (new_brk == NULL) {
    dld_perror ("dld_get_bare_symbol");
    return 1;
  }
  *new_brk = sbrk (0);
#endif /* sequent */

  /* Give a sign to the program so that it knows we loaded it. */
  switch ((*func) (2, newargv)) {
  case 0:
    return 0;

  case 1:
    fprintf (stderr, "%s: %s didn't think its argc was 2\n",
	     argv[0], RELOADME);
    break;
    
  case 2:
    fprintf (stderr,
	     "%s: %s didn't think its argv[0] was the same as argv[1]\n",
	     argv[0], RELOADME);
    break;

  default:
    fprintf (stderr,
	     "%s: unknown return code from %s\n", argv[0], RELOADME);
  }

  return 1;
}

