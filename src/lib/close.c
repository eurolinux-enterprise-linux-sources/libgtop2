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
#include <glibtop/open.h>
#include <glibtop/error.h>
#include <glibtop/close.h>
#include <glibtop/command.h>

/* Closes server. */

void
glibtop_close_r (glibtop *server)
{
	switch (server->method) {
	case GLIBTOP_METHOD_UNIX:
	case GLIBTOP_METHOD_INET:
		glibtop_call_l (server, GLIBTOP_CMND_QUIT,
				0, NULL, 0, NULL);

		if (close (server->socket))
			glibtop_warn_io ("close");

		break;
	case GLIBTOP_METHOD_PIPE:
		kill (server->pid, SIGKILL);
		close (server->input [0]);
		close (server->output [1]);
		break;
	}
}
