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
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <config.h>
#include <glibtop.h>
#include <glibtop/error.h>
#include <glibtop/uptime.h>

#include <time.h>

static const unsigned long _glibtop_sysdeps_uptime =
(1L << GLIBTOP_UPTIME_UPTIME);

/* Init function. */

void
_glibtop_init_uptime_s (glibtop *server)
{
	server->sysdeps.uptime = _glibtop_sysdeps_uptime;
}

/* Provides uptime and idle time. */

void
glibtop_get_uptime_s (glibtop *server, glibtop_uptime *buf)
{
	struct tbl_sysinfo sysinfo;

	glibtop_init_s (&server, GLIBTOP_SYSDEPS_UPTIME, 0);

	memset (buf, 0, sizeof (glibtop_uptime));

	if(table (TBL_SYSINFO, 0, (char *) &sysinfo, 1,
		   sizeof (struct tbl_sysinfo)) != 1)
	  return;

	buf->uptime = (double) (time (NULL) - sysinfo.si_boottime);
	buf->boot_time = sysinfo.si_boottime;

	buf->flags = _glibtop_sysdeps_uptime;
}
