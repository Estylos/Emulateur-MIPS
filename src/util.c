/**
 * @file util.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme de fonctions outils utiles à d'autres programmes.
 * @copyright Sous licence MIT
 * 
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void error(const char *file, int line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	fprintf(stderr, ANSI_CODE_RED "[ERROR] " ANSI_CODE_RESET
					ANSI_CODE_GREY " %s:%d: " ANSI_CODE_RESET, file, line);
	vfprintf(stderr, fmt, args);
#ifndef __DEBUG__
	fprintf(stderr, ANSI_CODE_GREY " (mode debug \"-D__DEBUG__\" pour plus d'informations)" ANSI_CODE_RESET);
#endif

	fputc('\n', stderr);
	va_end(args);
#ifndef __NO_CRASH_ON_ERROR__
	exit(1);
#endif
}

void runtimeError(const char *file, int line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	fprintf(stderr, ANSI_CODE_BG_RED "[RUNTIME ERROR] " ANSI_CODE_RESET
					ANSI_CODE_GREY " %s:%d: " ANSI_CODE_RESET, file, line);
	vfprintf(stderr, fmt, args);
#ifndef __DEBUG__
	fprintf(stderr, ANSI_CODE_GREY " (mode debug \"-D__DEBUG__\" pour plus d'informations)" ANSI_CODE_RESET);
#endif

	fputc('\n', stderr);
	va_end(args);
#ifndef __NO_CRASH_ON_ERROR__
	exit(1);
#endif
}

void warning(const char *file, int line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	fprintf(stderr, ANSI_CODE_YELLOW "[WARN] " ANSI_CODE_RESET
					ANSI_CODE_GREY " %s:%d: " ANSI_CODE_RESET, file, line);
	vfprintf(stderr, fmt, args);
#ifndef __DEBUG__
	fprintf(stderr, ANSI_CODE_GREY " (mode debug \"-D__DEBUG__\" pour plus d'informations)" ANSI_CODE_RESET);
#endif

	fputc('\n', stderr);
	va_end(args);
}

void debug(const char *file, int line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	fprintf(stderr, ANSI_CODE_CYAN "[DEBUG] " ANSI_CODE_RESET
					ANSI_CODE_GREY " %s:%d: " ANSI_CODE_RESET, file, line);
	vfprintf(stdout, fmt, args);

	fputc('\n', stdout);

	va_end(args);
}

void *emalloc(unsigned int n)
{
	void *p = NULL;

	p = malloc(n);
	if (p == NULL)
		LOG_ERROR("malloc");
	return p;
}

void *erealloc(void *q, unsigned int n)
{
	void *p = NULL;

	p = realloc(q, n);
	if (p == NULL)
		LOG_ERROR("realloc");
	return p;
}

FILE *efopen(const char *pathname, const char *mode)
{
	FILE *file = fopen(pathname, mode);
	if (file == NULL)
	{
		perror(pathname);
		LOG_ERROR("fopen");
	}
	return file;
}

char *estrtok(char *string, const char *delimiters)
{
	char *token = strtok(string, delimiters);
	if (token == NULL)
		LOG_ERROR("Nombre d'opérandes invalides pour une instruction");

	return token;
}