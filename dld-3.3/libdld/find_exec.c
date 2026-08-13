/* find_exec.c -- Find a program, given an argv[0]
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
#include <config.h>
#include <sys/types.h>
#include <pwd.h>
#include "system.h"

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <stdlib.h>
#include <sys/stat.h>
#ifdef HAVE_SYS_FILE_H
# include <sys/file.h>
#endif
#include <sys/param.h>
#include "dld.h"

extern PTR _dld_malloc PARAMS ((int size));

static char *
copy_of (const char *s)
{
  char *p = _dld_malloc (strlen (s) + 1);

  if (!p)
    return 0;

  *p = 0;
  strcpy (p, s);
  return p;
}

/* ABSOLUTE_FILENAME_P (fname): True if fname is an absolute filename */
#ifdef atarist
#define ABSOLUTE_FILENAME_P(fname)	((fname[0] == '/') || \
	(fname[0] && (fname[1] == ':')))
#else
#define ABSOLUTE_FILENAME_P(fname)	(fname[0] == '/')
#endif /* atarist */

/* Return the absolute name of the program named NAME.  This function
   searches the directories in the PATH environment variable if PROG
   has no directory components. */
char *
dld_find_executable (const char *name)
{
  char *search;
  char *p;
  char tbuf[MAXPATHLEN];

  if (ABSOLUTE_FILENAME_P(name)) {
      /* If we can execute the named file, and it is normal, then return it. */
      if (! access (name, X_OK)) {
	struct stat stat_temp;

	if (stat (name, &stat_temp))
	  return 0;

#ifndef STAT_MACROS_BROKEN
	if (! S_ISREG(stat_temp.st_mode))
	  return 0;
#endif
	return copy_of (name);
      }
    }
  else {
    if ((name[0] == '.') && (name[1] == '/')) {
      strcpy (tbuf, ".");

#ifdef HAVE_GETCWD
      getcwd (tbuf, MAXPATHLEN);
#else
# ifdef HAVE_GETWD
      getwd (tbuf);
# endif
#endif
      strcat (tbuf, name + 1);
      return copy_of (tbuf);
    }

    search = getenv ("PATH");
    p = search;

    while (*p) {
      char *next;
      next = tbuf;

      /* Perform tilde-expansion. Stolen from GNU readline/tilde.c. */
      if (p[0] == '~') {
	if (! p[1] || p[1] == '/') {
	  /* Prepend $HOME to the rest of the string. */
	  char *temp_home = (char *) getenv ("HOME");

	  /* If there is no HOME variable, look up the directory in the
	     password database. */
	  if (! temp_home) {
	    struct passwd *entry;

	    entry = getpwuid (getuid ());
	    if (entry)
	      temp_home = entry->pw_dir;
	  }

	  strcpy (tbuf, temp_home);
	  next = tbuf + strlen (tbuf);
	  p ++;
	}
	else {
	  char username[MAXPATHLEN];
	  struct passwd *user_entry;
	  int i;

	  p ++;			/* Skip the tilde. */
	  for (i = 0; *p && *p != '/' && *p != ':'; i++)
	    username[i] = *p ++;
	  username[i] = '\0';

	  user_entry = getpwnam (username);
	  if (user_entry) {
	    strcpy (tbuf, user_entry->pw_dir);
	    next = tbuf + strlen (tbuf);
	  }
	}

	endpwent ();
      }

      /* Copy directory name into [tbuf]. */
      while (*p && *p != ':')
	*next ++ = *p ++;
      *next = '\0';
      if (*p != '\0')
	p ++;

      if (tbuf[0] == '.' && tbuf[1] == '\0') {
#ifdef HAVE_GETCWD
	getcwd (tbuf, MAXPATHLEN);
#else
# ifdef HAVE_GETWD
	getwd (tbuf);
# endif
#endif
      }

      strcat (tbuf, "/");
      strcat (tbuf, name);

      /* If we can execute the named file, and it is normal, then return it. */
      if (! access (tbuf, X_OK)) {
	struct stat stat_temp;

	if (stat (tbuf, &stat_temp))
	  continue;

#ifndef STAT_MACROS_BROKEN
	if (! S_ISREG(stat_temp.st_mode))
	  continue;
#endif
	return copy_of (tbuf);
      }
    }
  }

  return 0;
}
