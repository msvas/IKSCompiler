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

//! Dictionary table
static comp_dict_t *dicttab = NULL;
//! number of entries
static uint32_t cnt;

comp_dict_item_t *lookup(const char *s)
{
	comp_dict_item_t *dip;
	for (dip = dicttab->fep; dip != NULL; dip = dip->next) {
		if (strcmp(s, dip->name) != 0)
			continue;
		return dip; /* found */
	}
	return NULL; /* not found */
}

comp_dict_item_t *install(const char *name, const char *def)
{
	comp_dict_item_t *dip;

	if ((dip = lookup(name)) == NULL) {
		/* not found */
		dip = (comp_dict_item_t *)malloc(sizeof(*dip));
		if (dip == NULL) {
			debug("Could not install (%s, %s)", name, def);
			return NULL;
		}
		dip->name = strdup(name);
		if (dip->name == NULL) {
			debug("Could not install (%s, %s)", name, def);
			free(dip);
			return NULL;
		}
		dip->next = NULL;

		if (dicttab == NULL) {
			/* first entry */
			dicttab = malloc(sizeof(*dicttab));
			if (dicttab == NULL) {
				debug("Could not install (%s, %s)", name, def);
				free(dip->name);
				free(dip);
				return NULL;
			}
			dicttab->fep = dip;
			dicttab->lep = dip;
			cnt++;
		} else {
			cnt++;
			dicttab = realloc(dicttab, sizeof(*dicttab) * cnt);
			dicttab->lep->next = dip;
			dicttab->lep = dip;
		}
	} else {
		/* 
		 * already there: free previous
		 * definition and write the new one 
		 */
		free((void *)dip->def);
	}
	
	dip->def = strdup(def);
	if (dip->def == NULL) {
		debug("Could not install (%s, %s)", name, def);
		free(dip->name);
		free(dip);
		return NULL;
	}

	return dip;
}

