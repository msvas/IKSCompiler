/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   util.h
 * @brief  General utilities.
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//! Enable/Disable debugs.
//#define DEBUG_ON
#ifdef DEBUG_ON
/**
 * Print utility that prints file and line. Useful for debug. It can replace
 * printf() with advantages. Usage is almost the same as printf().
 * E.g.:
 * debug("%s", "Hello world");
 */
#define debug(fmt, ...) printf("%s (%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(fmt, ...) do {} while (0);
#endif /* DEBUG_ON */

/* Array size macro */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

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

#endif /* __UTIL_H__ */

