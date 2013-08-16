/*
 * @file   comp_dict_tst.c
 * @brief  Dictionary tests base file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "comp_dict.h"
#include "util.h"

int main(int argc, char *argv[])
{
	int i;
	comp_dict_item_t *dip;
	char *k[] = { "ein", "zwei", "drei", "vier", "funf" };
	
	for (i = 0; i < ARRAY_SIZE(k); i++)
		install(k[i], i);

	show_dict();

	install("compiler", 98082);
	
	show_dict();

	dip = lookup("test");
	if (dip == NULL)
		debug("Key \"test\" not found.");
	else
		debug("Key \"test\" found (?!), val %d.", dip->val);

	install("compilers", 9);

	dip = lookup("compilers");
	if (dip == NULL)
		debug("Key \"compilers\" not found (?!).");
	else
		debug("Key \"compilers\" found, val %d.", dip->val);

	show_dict();

	/* release and go */
	free_dict();
	return 0;
}

