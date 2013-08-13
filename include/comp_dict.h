/*
 * @file   comp_dict.h
 * @brief  Dictionary realted functions prototypes and data types.
 */

#ifndef __COMPT_DICT_H__
#define __COMPT_DICT_H__

//! Dictionary element data
typedef struct dict_item {
	struct dict_item *next;	//!< next entry
	char *name;		//!< name of the item (the key)
	char *def;		//!< definition that replaces the key
} comp_dict_item_t;

//! Dictionary
typedef struct dict { 
	comp_dict_item_t *fep;	//!< first entry pointer
	comp_dict_item_t *lep;	//!< last entry pointer
} comp_dict_t;

/**
 * Look for s in dicttab
 * @param s: string to look up for.
 * @return pointer to the related entry if found, NULL
 * otherwise.
 */
comp_dict_item_t *lookup(const char *s);

/**
 * Put (name, def) in dicttab
 * @param name: name or key for an entry.
 * @param def: definition or replacement text.
 * @return on success a pointer to the new entry is
 * returned, NULL otherwise.
 */
comp_dict_item_t *install(const char *name, const char *def);

#endif /* __COMPT_DICT_H__ */

