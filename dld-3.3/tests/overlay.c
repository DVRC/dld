/* overlay.c -- overlay a function several times
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
#include <stdlib.h>
#include <dld.h>

#if 0
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include "overlay.h"

/* strings to hold the next object file to be linked.  On invocation, the
   linked-in function will modify this string so that a different file will
   be loaded next time. */
char *p;

/*
 *  Show how different modules can be overlayed onto the same memory
 *  sections.
 */
int
main (int argc, char **argv)
{
  /* FIXME: Don't use rusage, it produces unpredictable test results!
   * Maybe we'll be able to with dejagnu. */
#if 0
  struct rusage rusage;
#endif
  
  int chain_num = 0;
  p = malloc (MAX_NAME);
  strcpy (p, CHAIN1);
  
  if (dld_init (argv[0]) != 0) {
    dld_perror ("dld_init");
    return 1;
  }
  
#if 0
  /* Use the max. memory allocation to show that all the dynamically
     linked in modules indeed share the (more or less) same memory
     sections.  Each module contains a large static array.  If they are
     not overlayed, the max. RSS will increase. */
  getrusage (RUSAGE_SELF, &rusage);
  printf ("MAX_RSS = %d page.\n", rusage.ru_maxrss);
#endif
  
  do {
    void (* func) (void);
	
    dld_errno = dld_link (p);
    if (dld_errno) {
      dld_perror ("dld_link (" CHAIN1 ")");
      return 1;
    }

#if 0
    getrusage (RUSAGE_SELF, &rusage);
    printf ("MAX_RSS = %d page.\n", rusage.ru_maxrss);
#endif
    if (dld_function_executable_p("chain")) {
      func = (void (*) (void)) dld_get_func ("chain");

      if (func == NULL) {
	dld_perror ("dld_get_func");
	return 1;
      }
      (* func) ();
    }
    else {
      fprintf (stderr,
	       "%s: \"chain\" is not an executable function in %s\n",
	       argv[0], p);
      return 0;
    }
	  
    if (dld_unlink_by_symbol ("chain", 0) != 0) {
      dld_perror ("dld_unlink_by_symbol");
    }
    
    chain_num ++;
  } while (p != 0 && chain_num <= MAX_CHAINS);

  if (chain_num > MAX_CHAINS) {
    fprintf (stderr, "%s: interrupting a potential infinite loop\n", argv[0]);
    return 1;
  }
  if (chain_num < MAX_CHAINS) {
    fprintf (stderr, "%s: only loaded up to chain %d\n", argv[0], chain_num);
    return 1;
  }

  return 0;
}


/* FIXME: guarantee that the C library provides functions this test needs. */
void
libc_funcs_needed_by_tests (void)
{
  /* Needed by chain*.o */
  memset (NULL, 0, 0);
}
