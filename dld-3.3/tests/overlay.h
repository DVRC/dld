/* overlay.h - declarations of parts of the overlay program.
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
#include <config.h>
#include <sys/types.h>
#include "system.h"

extern char *p;

/* Enough space for any of the chain names. */
#define MAX_NAME 10
#define MAX_CHAINS 3
#define CHAIN1 "chain1.o"
#define CHAIN2 "chain2.o"
#define CHAIN3 "chain3.o"

void chain (void);
