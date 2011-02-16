/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008-2011 WiredTiger, Inc.
 *	All rights reserved.
 */

#include "wt_internal.h"

/*
 * __wt_sleep --
 *	Pause the thread of control.
 */
void
__wt_sleep(long seconds, long micro_seconds)
{
	struct timeval t;

	t.tv_sec = (long)seconds + micro_seconds / 1000000;
	t.tv_usec = (long)micro_seconds % 1000000;

	(void)select(0, NULL, NULL, NULL, &t);
}
