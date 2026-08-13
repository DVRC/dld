/* general.c -- a generalized link/unlink utility
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
#include <config.h>
#include <sys/types.h>
#include "system.h"

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <dld.h>

#define MAXLINE 80

int my_argc;
char **my_argv;

void parse (char *line);
void execute (int my_argc, char **my_argv);

/*
 *  Ask for a object file interactively, then link it in.
 *  User can then enter the function name for execution.
 *  See file "SAMPLE_INPUT" for an example.
 */
int
main (int argc, char **argv)
{
  char line[MAXLINE];

  /* Required initialization. */
  if (dld_init (argv[0]) != 0) {
    dld_perror ("dld_init");
  }
    
  my_argv = 0;
  printf ("(dld) ");
  while (fgets (line, MAXLINE, stdin) != NULL) {
    if (strlen (line) == MAXLINE - 1) {
      fprintf (stderr, "%s: oops... the buffer was overrun\n", argv[0]);
      return 1;
    }

    printf ("%s", line);
    if (my_argv)
      free (my_argv);

    parse (line);
    execute (my_argc, my_argv);
    printf ("(dld) ");
  }
    
  return 0;
}

/* parse the user input.  Split the arguments into my_argv and put number
   of arguments in my_argc, in the same way as the shell parse the command
   line arguments. */
void
parse (char *line)
{
  char *p;

  my_argc = 0;
  p = line;

  while (*p) {
    while (isspace (*p))
      p++;

    if (*p == '\0')
      break;

    while (! isspace (*p) && *p != '\0')
      p++;

    my_argc++;
    if (*p != '\0')
      p++;
  }

  my_argv = (char **) malloc ((my_argc + 1) * sizeof (char **));
    
  {
    int i;
    p = line;

    for (i = 0; i < my_argc; i ++) {
      while (isspace (*p))
	p++;

      my_argv[i] = p;

      while (!isspace (*p) && *p != '\0')
	p++;

      *p = '\0';
      p++;
    }

    my_argv[my_argc] = '\0';
  }
} /* parse */


/*
 *  Carry out the user command:
 *  dld object_file.o			-- dynamically link in that file.
 *  ul object_file.o			-- unlink that file.
 *  uls function_name			-- unlink that function.
 *  function_name arg1 arg2 ...		-- execute that function.
 */
void
execute (int my_argc, char **my_argv)
{
  int (*func) ();
    
  if (my_argc == 0)
    return;

  if (! strcmp (my_argv[0], "dld"))
    while (-- my_argc) {
      if (dld_link (*(++my_argv)) != 0)
	dld_perror ("dld_link");
    }
  else if (!strcmp (my_argv[0], "ul"))
    dld_unlink_by_file (my_argv[1], my_argc >= 3 ? 1 : 0);
  else if (!strcmp (my_argv[0], "uls"))
    dld_unlink_by_symbol (my_argv[1], my_argc >= 3 ? 1 : 0);
  else {
    func = (int (*) ()) dld_get_func (my_argv[0]);
    if (func) {
      int i;
      if (dld_function_executable_p (my_argv[0])) {
	i = (*func) (my_argc, my_argv);
	if (i)
	  printf ("%d\n", i);
      } else
	printf ("%s is not executable\n", my_argv[0]);
    }
    else
      printf ("illegal command\n");
  }
}


/* FIXME: guarantee that the C library provides functions this test needs. */
void
libc_funcs_needed_by_tests (void)
{
  /* Needed by most objects. */
  printf (NULL);

  /* Needed by read-a.out.o */
  fopen (NULL, NULL);
  fread (NULL, 0, 0, NULL);
  fseek (NULL, 0, 0);

  /* Needed by need.o */
  fflush (NULL);
}
