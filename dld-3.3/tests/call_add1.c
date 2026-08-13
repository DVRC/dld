/* call_add1.c -- a simple test of dynamic linking
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
#include <dld.h>
    
int GLOBAL_VAR;

/*
 *  Dynamically link in "add1.o", which defines the function ADD1.
 *  Invoke ADD1 to increment the global variable GLOBAL_VAR defined *here*.
 */
int
main (int argc, char **argv)
{
    void (*func) ();

    GLOBAL_VAR = 1;
    if (dld_init (argv[0]) != 0) {
      dld_perror ("dld_init");
      return 1;
    }

    /* Grab the entry point for function ADD1. */
    if (dld_link ("add1.o") != 0) {
      dld_perror ("dld_link");
      return 1;
    }

    func = (void (*) (void)) dld_get_func ("add1");
    if (func == 0) {
      dld_perror ("dld_get_func");
      return 1;
    }      

    /* Invoke ADD1. */
    (*func) ();
    if (GLOBAL_VAR == 2) {
      return 0;
    }

    return 1;
}
