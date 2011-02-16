/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008-2011 WiredTiger, Inc.
 *	All rights reserved.
 *
 * ex_transaction.c
 *	This is an example demonstrating how to use transactions.
 */

#include <stdio.h>
#include <string.h>

#include <wiredtiger.h>

const char *home = "WT_TEST";

int main()
{
	int ret;
	WT_CONNECTION *conn;
	WT_SESSION *session;

	/* Open a connection to the database, creating it if necessary. */
	if ((ret = wiredtiger_open(home, NULL, "create,transactional", &conn)) != 0)
		fprintf(stderr, "Error connecting to %s: %s\n",
		    home, wiredtiger_strerror(ret));

	/* Open a session for the current thread's work. */
	if ((ret = conn->open_session(conn, NULL, NULL, &session)) != 0)
		fprintf(stderr, "Error opening a session on %s: %s\n",
		    home, wiredtiger_strerror(ret));

	session->begin_transaction(session, NULL);
	/* ... */
	session->commit_transaction(session, NULL);

	/* Note: closing the connection implicitly closes open session(s). */
	if ((ret = conn->close(conn, NULL)) != 0)
		fprintf(stderr, "Error connecting to %s: %s\n",
		    home, wiredtiger_strerror(ret));

	return (ret);
}
