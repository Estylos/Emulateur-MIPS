/**
 * @file memory.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme simulant la mémoire volatile.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "util.h"
#include "memory.h"


/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

#define NULL_MEM_CELL (MemoryCell *)0
#define UNSET_MEMORY_VALUE (uint32_t) rand()


/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/

typedef struct memoryCell
{
	uint32_t address;
	uint32_t value;
	struct memoryCell *next;
} MemoryCell;


/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

MemoryCell *memory = NULL_MEM_CELL;


/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static MemoryCell *findMemoryCell(uint32_t address);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void initMemory(void)
{
	srand(time(NULL));
	freeMemory();
}

void freeMemory(void)
{
	if (memory != NULL_MEM_CELL)
	{
		MemoryCell *toFree = memory;
		MemoryCell *next;
		do
		{
			next = toFree->next;
			free(toFree);
			toFree = next;
		} while (toFree != NULL_MEM_CELL);
	}
	memory = NULL_MEM_CELL;
}

uint32_t getMemory(const uint32_t address)
{
	uint32_t r;
	MemoryCell *mc = findMemoryCell(address);

	if (mc == NULL_MEM_CELL)
		r = UNSET_MEMORY_VALUE;
	else
		r = mc->value;

	return r;
}

void setMemory(const uint32_t address, const uint32_t value)
{
	MemoryCell *mc = findMemoryCell(address);
	if (mc == NULL_MEM_CELL)
	{
		// ajout en tête
		MemoryCell *newMc = emalloc(sizeof(MemoryCell));
		newMc->address = address;
		newMc->value = value;
		newMc->next = memory;
		memory = newMc;
	}
	else
	{
		mc->value = value;
	}
}

void printMemory(FILE *stream)
{
	if (stream == stdout)
	{
		printf(ANSI_CODE_BOLD "ETAT DE LA MEMOIRE\n");
		printf("-------------------\n" ANSI_CODE_RESET);
	}

	MemoryCell *mCell = memory;

	while (mCell != NULL_MEM_CELL)
	{
		fprintf(stream, "0x%08X : %d\n", mCell->address, mCell->value);
		mCell = mCell->next;
	}

	if (stream == stdout)
	{
		printf(ANSI_CODE_BOLD "-------------------\n" ANSI_CODE_RESET);
	}
}

/**
 * @brief Fonction servant à chercher une adresse en mémoire.
 * Si l'adresse n'est pas en mémoire, la fonction renvoie un pointeur NULL.
 * 
 * @param address Adresse cherchée en mémoire 
 * @return mc : Pointeur vers la structure MemoryCell ayant l'adresse donnée en mémoire 
 */
static MemoryCell *findMemoryCell(uint32_t address)
{
	if (memory != NULL_MEM_CELL)
	{
		MemoryCell *mCell = memory;
		do
		{
			if (mCell->address == address)
				return mCell;
			mCell = mCell->next;
		} while (mCell != NULL_MEM_CELL);
	}
	return NULL_MEM_CELL;
}