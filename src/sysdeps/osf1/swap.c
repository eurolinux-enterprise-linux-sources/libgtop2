/* Copyright (C) 1998-99 Martin Baulig
   This file is part of LibGTop 1.0.

   Contributed by Martin Baulig <martin@home-of-linux.org>, April 1998.

   LibGTop is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   LibGTop is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with LibGTop; see the file COPYING. If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <config.h>
#include <glibtop.h>
#include <glibtop/error.h>
#include <glibtop/swap.h>

static const unsigned long _glibtop_sysdeps_swap =
(1L << GLIBTOP_SWAP_TOTAL) + (1L << GLIBTOP_SWAP_USED) +
(1L << GLIBTOP_SWAP_FREE);

/* Init function. */

void
_glibtop_init_swap_s (glibtop *server)
{
	server->sysdeps.swap = _glibtop_sysdeps_swap;
}

/* Provides information about swap usage. */

void
glibtop_get_swap_s (glibtop *server, glibtop_swap *buf)
{
	struct tbl_swapinfo swapinfo;
	int i;

	glibtop_init_s (&server, GLIBTOP_SYSDEPS_SWAP, 0);

	memset (buf, 0, sizeof (glibtop_swap));

	i = 0;

	while (table (TBL_SWAPINFO, i, (char *) &swapinfo, 1,
		      sizeof (struct tbl_swapinfo)) > 0) {
		buf->total += swapinfo.size * getpagesize ();
		buf->free  += swapinfo.free * getpagesize ();
		i++;
	}

	buf->flags = _glibtop_sysdeps_swap;

	buf->used  = buf->total - buf->free;
}
