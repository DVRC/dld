/* system.h -- system-dependent header file
   Copyright (C) 1996 Free Software Foundation, Inc.
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

/* Written by Gordon Matzigkeit <gord@gnu.ai.mit.edu> */

/* Declare some standard functions. */
#if STDC_HEADERS
# include <string.h>
#else
#if PROTOTYPES
char *strcat (char *dest, const char *src);
void *memset (void *dest, int val, size_t len);
#else
char *strcat ();
void *memset ();
#endif
# ifndef HAVE_MEMCPY
#  define memcpy(d, s, n) bcopy ((s), (d), (n))
#  define memmove(d, s, n) bcopy ((s), (d), (n))
# endif
#endif
