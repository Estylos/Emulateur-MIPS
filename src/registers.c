/**
 * @file registers.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme simulant les registres du processeur.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"
#include "registers.h"


/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

#define REGISTERS_NB 		(32 + 1 + 2)
#define REGISTERS_DEFAULT 	0
#define PC_DEFAULT 			0
#define SP_DEFAULT			0


/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

uint32_t registers[REGISTERS_NB];
int64_t jumpAtNextIncreasePc = -1;


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void initRegisters(void)
{
	for (unsigned char i = 0; i < REGISTERS_NB; i++)
	{
		registers[i] = REGISTERS_DEFAULT;
	}
	registers[0] = 0;
	registers[REG_PC] = PC_DEFAULT;
	registers[REG_SP] = SP_DEFAULT;
}

uint32_t getRegister(const unsigned char regNumber)
{
	return registers[regNumber];
}

void setRegister(const unsigned char regNumber, const uint32_t val)
{
	if (regNumber == 0 || regNumber == 26 || regNumber == 27)
	{
		// do nothing
	}
	else
	{
		registers[regNumber] = val;
	}
}

void increasePc(const int instructionsNb)
{
	if (jumpAtNextIncreasePc == -1)
		registers[REG_PC] += instructionsNb * 4;
	else
		registers[REG_PC] = (uint32_t)jumpAtNextIncreasePc;

	jumpAtNextIncreasePc = -1;
}

uint32_t getPcInstructionsNb(void)
{
	return registers[REG_PC] / 4;
}

void setJumpAtNextIncreasePc(const uint32_t address)
{
	jumpAtNextIncreasePc = (int64_t)address;
}

void printRegister(FILE *stream)
{
	if (stream == stdout)
	{
		printf(ANSI_CODE_BOLD "ETATS DES REGISTRES\n");
		printf("-------------------\n" ANSI_CODE_RESET);
	}

	for (unsigned char i = 0; i <= 31; i++)
		fprintf(stream, "$%02d: %d\n", i, registers[i]);
	fprintf(stream, "HI: %d\n", registers[REG_HI]);
	fprintf(stream, "LO: %d\n", registers[REG_LO]);

	if (stream == stdout)
	{
		printf(ANSI_CODE_BOLD "-------------------\n" ANSI_CODE_RESET);
	}
}
