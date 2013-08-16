/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   util.h
 * @brief  General utilities.
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

//! Enable/Disable debugs.
#define DEBUG_ON
#ifdef DEBUG_ON
/**
 * Print utility that prints file and line. Useful for debug. It can replace
 * printf() with advantages. Usage is almost the same as printf().
 * E.g.:
 * debug("%s", "Hello world");
 */
#define debug(fmt, ...) printf("%s (%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif /* DEBUG_ON */

#endif /* __UTIL_H__ */

