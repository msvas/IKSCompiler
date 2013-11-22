/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_dict_tst.c
 * @brief  Dictionary routines test file.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "comp_dict.h"
#include "util.h"

/**
 * Creates a unique file name (the complete path) and returns a pointer to it.
 * @return on success a pointer to the file name created is returned, otherwise NULL.
 * Note:
 * Memory is dynamic allocated and must be freed() by the caller.
 */
static char *get_unique_fname()
{
	char *template = NULL;
	char *cwd;
	int fd;

	/* get current dir name */
	cwd = get_current_dir_name();
	if (cwd == NULL) {
		debug("%s", strerror(errno));
		return NULL;
	}

	/* create a path template */
	asprintf(&template, "%s/symtab-XXXXXX", cwd);

	/* get a unique file name */
	if ((fd = mkstemp(template)) == -1) {
		debug("%s", strerror(errno));
		return NULL;
	}
	close(fd);
	remove(template);

	return template;
}

/**
 * Checks if a file exist.
 * @param path: file path.
 * return 1 if file exists, 0 otherwise.
 */
static int file_exists(const char *path)
{
	struct stat s;
	return (stat(path, &s) == 0);
}

/**
 * Creates a symbol table file.
 * @param path: file path.
 * return 0 on success, -1 on error.
 */
static int create_symbol_file(const char *path)
{
	FILE *output;
	comp_dict_item_t *dip;
	char *sfn = NULL;

	if (path == NULL) {
		/* 
		 * User hasn't specified a path.
		 * Let's create an unique file name to him.
		 */
		sfn = get_unique_fname();
		if (sfn == NULL) {
			debug("Could not get a name to the symbol file");
			return -1;
		} 
	} else {
		/*
		 * Let's check if the file specified already exsit, so we can
		 * ask before overwrite the file. The intent is avoiding damage
		 * the system.
		 */
		if (file_exists(path)) {
			char ans;
			printf("File \"%s\" already exists and will be overwritten.\n", path);
			printf("Shall I continue (y/n)? ");
			scanf("%c", &ans);
			switch (ans) {
				case 'y':
				case 'Y':
					break;
				default:
					return -1;
			}
		}
	}

	output = fopen((path != NULL) ? path : sfn, "w+");
	if (output == NULL) {
		debug("%s", strerror(errno));
		return -1;
	}

	/* "shows" data into the file */
	show_dict(output);

	fclose(output);

	printf("-- Symbol file created at %s\n", (path != NULL) ? path : sfn);
	return 0;
}


int main(int argc, char *argv[])
{
	int rv = 0;
	int i;
	comp_dict_item_t *dip;
	char *k[] = { "ein", "zwei", "drei", "vier", "funf" };

	for (i = 0; i < ARRAY_SIZE(k); i++)
		install(k[i], i, i);

	install("compiler", 98765, i + 1);
	
	dip = lookup("test");
	if (dip == NULL) {
		debug("Key \"test\" not found.");
	} else {
		debug("Key \"test\" found (?!), val %d.", dip->val);
	}

	install("compilers", 9, i + 2);

	dip = lookup("compilers");
	if (dip == NULL) {
		debug("Key \"compilers\" not found (?!).");
	} else {
		debug("Key \"compilers\" found, val %d.", dip->val);
	}

	create_symbol_file(NULL);

	/* release and go */
	free_dict();
	return rv;
}

