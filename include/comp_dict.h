/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_dict.h
 * @brief  Dictionary realted functions prototypes and data types.
 */

#ifndef __COMPT_DICT_H__
#define __COMPT_DICT_H__

#include <stdint.h>

//! Dictionary element data
typedef struct dict_item {
	struct dict_item *next;	//!< next entry
	char *key;		//!< key of the item (attribute value)
	uint32_t val;		//!< value associated to the key (token name)
	uint32_t l;		//!< line number the entry was found
} comp_dict_item_t;

//! Dictionary
typedef struct dict { 
	comp_dict_item_t *fep;	//!< first entry pointer
	comp_dict_item_t *lep;	//!< last entry pointer
	uint32_t cnt;		//!< number of entries
} comp_dict_t;

/**
 * Look for s in dicttab
 * @param k: key to look up for.
 * @return pointer to the related entry if found, NULL
 * otherwise.
 */
comp_dict_item_t *lookup(const char *k);

/**
 * Put (key, val) in dicttab
 * @param key: key for an entry.
 * @param val: value associated to that entry.
 * @param line: line the entry was found.
 * @return on success a pointer to the new entry is
 * returned, NULL otherwise.
 */
comp_dict_item_t *install(const char *key, uint32_t val, uint32_t line);

/**
 * Display all entries (key, val) in the dictionary
 * @param out: output stream
 */
void show_dict(FILE *out);

/**
 * Creates a symbol file from dictionary data.
 * @param path: file path.
 * @return 0 on success, -1 otherwise.
 */
int create_symbol_file(const char *path);

/**
 * Release resources previously allocated for this
 * dictionary.
 */
void free_dict(void);

#endif /* __COMPT_DICT_H__ */

