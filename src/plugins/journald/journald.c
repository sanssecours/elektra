/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the BSD License (revised).                      *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This is the skeleton of the methods you'll have to implement in order *
 *   to provide a valid plugin.                                            *
 *   Simple fill the empty functions with your code and you are            *
 *   ready to go.                                                          *
 *                                                                         *
 ***************************************************************************/


#ifndef HAVE_KDBCONFIG
# include "kdbconfig.h"
#endif

#include <stdlib.h>
#include <unistd.h>
#include <systemd/sd-journal.h>

#include "journald.h"

int elektraJournaldGet(Plugin *handle ELEKTRA_UNUSED, KeySet *returned ELEKTRA_UNUSED, Key *parentKey ELEKTRA_UNUSED)
{
	KeySet *n;
	ksAppend (returned, n = ksNew (30,
		keyNew ("system/elektra/modules/journald",
			KEY_VALUE, "journald plugin waits for your orders", KEY_END),
		keyNew ("system/elektra/modules/journald/exports", KEY_END),
		keyNew ("system/elektra/modules/journald/exports/get",
			KEY_FUNC, elektraJournaldGet,
			KEY_END),
		keyNew ("system/elektra/modules/journald/exports/set",
			KEY_FUNC, elektraJournaldSet,
			KEY_END),
		keyNew ("system/elektra/modules/journald/exports/error",
			KEY_FUNC, elektraJournaldError,
			KEY_END),
		keyNew ("system/elektra/modules/journald/infos",
			KEY_VALUE, "All information you want to know", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/author",
			KEY_VALUE, "Felix Berlakovich <elektra@berlakovich.net>", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/licence",
			KEY_VALUE, "BSD", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/description",
			KEY_VALUE, "Logs set and error calls to journald", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/provides",
			KEY_VALUE, "filter", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/placements",
			KEY_VALUE, "postcommit postrollback", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/needs",
			KEY_VALUE, "", KEY_END),
		keyNew ("system/elektra/modules/journald/infos/version",
			KEY_VALUE, PLUGINVERSION, KEY_END),
		KS_END));
	ksDel (n);
	return 1;
}

int elektraJournaldSet(Plugin *handle ELEKTRA_UNUSED, KeySet *returned ELEKTRA_UNUSED, Key *parentKey ELEKTRA_UNUSED)
{
        sd_journal_send ("MESSAGE=committed configuration %s with %zd keys",
        		keyName (parentKey),
        		ksGetSize (returned),
        		"MESSAGE_ID=fc65eab25c18463f97e4f9b61ea31eae",
        		"PRIORITY=5",
        		"HOME=%s", getenv ("HOME"),
        		"TERM=%s", getenv ("TERM"),
        		"PAGE_SIZE=%li", sysconf (_SC_PAGESIZE),
        		"N_CPUS=%li", sysconf (_SC_NPROCESSORS_ONLN),
        		NULL);
        return 1;
}

int elektraJournaldError(Plugin *handle ELEKTRA_UNUSED, KeySet *returned ELEKTRA_UNUSED, Key *parentKey ELEKTRA_UNUSED)
{
        sd_journal_send ("MESSAGE=rollback configuration %s with %zd keys",
        		keyName (parentKey),
        		ksGetSize (returned),
        		"MESSAGE_ID=fb3928ea453048649c61d62619847ef6",
        		"PRIORITY=5",
        		"HOME=%s", getenv ("HOME"),
        		"TERM=%s", getenv ("TERM"),
        		"PAGE_SIZE=%li", sysconf (_SC_PAGESIZE),
        		"N_CPUS=%li", sysconf (_SC_NPROCESSORS_ONLN),
        		NULL);

	return 1; /* success */
}

Plugin *ELEKTRA_PLUGIN_EXPORT(journald)
{
	return elektraPluginExport ("journald",
		ELEKTRA_PLUGIN_GET,	&elektraJournaldGet,
		ELEKTRA_PLUGIN_SET,	&elektraJournaldSet,
		ELEKTRA_PLUGIN_ERROR,	&elektraJournaldError,
		ELEKTRA_PLUGIN_END);
}

