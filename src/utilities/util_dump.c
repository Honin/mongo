/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008-2011 WiredTiger, Inc.
 *	All rights reserved.
 */

#include "wt_internal.h"
#include "util.h"

const char *progname;

int	usage(void);

int
main(int argc, char *argv[])
{
	extern char *optarg;
	extern int optind;
	DB *db;
	u_int32_t flags;
	int ch, ret, tret;

	WT_UTILITY_INTRO(progname, argv);

	flags = 0;
	while ((ch = getopt(argc, argv, "df:p")) != EOF)
		switch (ch) {
		case 'd':
			flags = WT_DEBUG;
			break;
		case 'f':			/* output file */
			if (freopen(optarg, "w", stdout) == NULL) {
				fprintf(stderr, "%s: %s: reopen: %s\n",
				    progname, optarg, strerror(errno));
				return (EXIT_FAILURE);
			}
			break;
		case 'p':
			flags = WT_PRINTABLES;
			break;
		case 'V':			/* version */
			printf("%s\n", wiredtiger_version(NULL, NULL, NULL));
			return (EXIT_SUCCESS);
		case '?':
		default:
			return (usage());
		}
	argc -= optind;
	argv += optind;

	/* The remaining argument is the database name. */
	if (argc != 1)
		return (usage());

	if ((ret = wiredtiger_simple_setup(progname, &db, 0, 0)) == 0) {
		if ((ret = db->open(db, *argv, 0, 0)) != 0) {
			db->err(db, ret, "Db.open: %s", *argv);
			goto err;
		}
		if ((ret = db->dump(db, stdout, NULL, flags)) != 0) {
			db->err(db, ret, "Db.dump");
			goto err;
		}
	}

	if (0) {
err:		ret = 1;
	}
	if ((tret = wiredtiger_simple_teardown(progname, db)) != 0 && ret == 0)
		ret = tret;
	return (ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int
usage()
{
	(void)fprintf(stderr,
	    "usage: %s [-dpV] [-f output-file] database\n", progname);
	return (EXIT_FAILURE);
}
