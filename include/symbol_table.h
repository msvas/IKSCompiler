/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_dict.h
 * @brief  Symbol table header file.
 */

#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

/**
 * Creates a unique file name (the complete path) and returns a pointer to it.
 * @return on success a pointer to the file name created is returned, otherwise NULL.
 * Note:
 * Memory is dynamic allocated and must be freed() by the caller.
 */
char *get_unique_fname(void);

/**
 * Creates a symbol table file.
 * @param path: file path.
 * return 0 on success, -1 on error.
 */
int create_symbol_file(const char *path);

#endif /* __SYMBOL_TABLE_H__ */

