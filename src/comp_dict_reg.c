/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_dict.c
 * @brief  Dictionary manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "comp_dict.h"
#include "util.h"

// TODO: maybe we should use a hashtable, it very probably scales better.
// Question0: how to define the hashtable size (number of elements)?
// Question1: how to enlarge the hashtable during compiling process?

//! Dictionary table
static comp_dict_t *dicttab = NULL;

comp_dict_item_t *lookup(const char *k)
{
	comp_dict_item_t *dip;

	/* dictionary has not been initialized yet */
	if (dicttab == NULL)
		return NULL;

	for (dip = dicttab->fep; dip != NULL; dip = dip->next) {
		if (strcmp(k, dip->key) != 0)
			continue;
		return dip; /* found */
	}
	return NULL; /* not found */
}

comp_dict_item_t *install(const char *key, uint32_t val, uint32_t line)
{
	comp_dict_item_t *dip;

	/* entry is already there, nothing to do */
	if ((dip = lookup(key)) != NULL)
		return dip;

	/* not found */
	dip = (comp_dict_item_t *)malloc(sizeof(*dip));
	if (dip == NULL) {
		debug("Could not install (%s, %d)", key, val);
		return NULL;
	}
	dip->key = strdup(key);
	if (dip->key == NULL) {
		debug("Could not install (%s, %d)", key, val);
		free(dip);
		return NULL;
	}
	dip->next = NULL;

	if (dicttab == NULL) {
		/* first entry */
		dicttab = malloc(sizeof(*dicttab));
		if (dicttab == NULL) {
			debug("Could not install (%s, %d)", key, val);
			free(dip->key);
			free(dip);
			return NULL;
		}
		dicttab->fep = dip;
		dicttab->lep = dip;
	} else {
		dicttab->lep->next = dip;
		dicttab->lep = dip;
	}

	/* increment the entries counter */
	dicttab->cnt++;

	dip->val = val;
	dip->l = line;

	return dip;
}

void show_dict(FILE *out)
{
	FILE *outstream;
	comp_dict_item_t *dip;

	outstream = out ? out : stdout;

	for (dip = dicttab->fep; dip != NULL; dip = dip->next) {
		fprintf(outstream, "%d: (%d, %s)\n", dip->l, dip->val, dip->key);
	}
}

void free_dict()
{
	comp_dict_item_t *dip;
	comp_dict_item_t *next;

	/* point the first entry */
	dip = dicttab->fep;
	while (dip != NULL) {
		/* free memory, key and node */
		next = dip->next;
		free(dip->key);
		free(dip);
		dip = next;
	}
	
	/* free the base structure */
	free(dicttab);
	dicttab = NULL;
}
