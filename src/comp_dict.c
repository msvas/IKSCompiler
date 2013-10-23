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
#include "iks_ast.h"

// TODO: maybe we should use a hashtable, it very probably scales better.
// Question0: how to define the hashtable size (number of elements)?
// Question1: how to enlarge the hashtable during compiling process?

//! Dictionary table
//static comp_dict_t *dicttab = NULL;

comp_dict_item_t *lookup(const char *k, comp_dict_t *dicttab)
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

comp_dict_t *installTable(const char *key, uint32_t val, int arrayString, uint32_t line, comp_dict_t *dicttab)
{
	comp_dict_item_t *dip;
	int size = 0;
	
	/* entry is already there, nothing to do */
	if ((dip = lookup(key, dicttab)) != NULL)
		return NULL;

	/* not found */

	switch(val) {
		case IKS_INT:
			size = 4;
			break;
		case IKS_FLOAT:
			size = 8;
			break;
		case IKS_CHAR:
			size = 1;
			break;
		case IKS_STRING:
			size = strlen(key);
			break;
		case IKS_BOOL:
			size = 1;
			break;
	}

	if(arrayString) {
		size = size*arrayString;
	}
	
	dip = (comp_dict_item_t *)malloc(size*(sizeof(*dip)));
		
	if (dip == NULL) {
		debug("Could not install (%s, %d)", key, val, dicttab);
		return NULL;
	}
	dip->key = strdup(key);
	
	if (dip->key == NULL) {
		debug("Could not install (%s, %d)", key, val, dicttab);
		free(dip);
		return NULL;
	}
	dip->next = NULL;

	if (dicttab == NULL) {
		/* first entry */
		dicttab = malloc(sizeof(*dicttab));
		if (dicttab == NULL) {
			debug("Could not install (%s, %d)", key, val, dicttab);
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

	if(arrayString) {
		dip->array = 1; //printf("oi");
	}
	else
		dip->array = 0;

	dip->val = val;
	dip->l = line;

	return dicttab;
}

comp_dict_item_t *install(const char *key, uint32_t val, uint32_t line, comp_dict_t *dicttab)
{
	comp_dict_item_t *dip;

	/* entry is already there, nothing to do */
	if ((dip = lookup(key, dicttab)) != NULL)
		return NULL;

	/* not found */
	dip = (comp_dict_item_t *)malloc(sizeof(*dip));
	if (dip == NULL) {
		debug("Could not install (%s, %d)", key, val, dicttab);
		return NULL;
	}
	dip->key = strdup(key);
	if (dip->key == NULL) {
		debug("Could not install (%s, %d)", key, val, dicttab);
		free(dip);
		return NULL;
	}
	dip->next = NULL;

	if (dicttab == NULL) {
		/* first entry */
		dicttab = malloc(sizeof(*dicttab));
		if (dicttab == NULL) {
			debug("Could not install (%s, %d)", key, val, dicttab);
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

void show_dict(comp_dict_t *dicttab)
{
	comp_dict_item_t *dip;

	for (dip = dicttab->fep; dip != NULL; dip = dip->next) {
		printf("%d: (%d, %s)\n", dip->l, dip->val, dip->key);
	}
}

int typeDefiner(int firstType, int secondType)
{
	if(firstType == IKS_INT && secondType == IKS_INT) {
		return IKS_INT;
	}
	else if (firstType == IKS_FLOAT && secondType == IKS_FLOAT) {
		return IKS_FLOAT;
	}
	else if (firstType == IKS_BOOL && secondType == IKS_BOOL) {
		return IKS_BOOL;
	}
	else if (firstType == IKS_FLOAT && secondType == IKS_INT) {
		return IKS_FLOAT;
	}
	else if (firstType == IKS_INT && secondType == IKS_FLOAT) {
		return IKS_FLOAT;
	}
	else if (firstType == IKS_BOOL && secondType == IKS_INT) {
		return IKS_INT;
	}
	else if (firstType == IKS_INT && secondType == IKS_BOOL) {
		return IKS_INT;
	}
	else if (firstType == IKS_FLOAT && secondType == IKS_BOOL) {
		return IKS_FLOAT;
	}
	else if (firstType == IKS_BOOL && secondType == IKS_FLOAT) {
		return IKS_FLOAT;
	}
	else {
		return 0;
	}
}

void free_dict(comp_dict_t *dicttab)
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

