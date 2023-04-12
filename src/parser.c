/**
 * @file parser.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Parseur de fichiers source assembleur.
 * @copyright Sous licence MIT
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "instructions.h"
#include "parser.h"
#include "util.h"

/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

Instruction **g_instructions;
unsigned int g_instructions_count;


/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static char isInstruction(char *line);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void parseAssemblyFile(char *assemblyFileLocation)
{
	LOG_DEBUG("Chargement du fichier assembleur %s", assemblyFileLocation);
	FILE *assemblyFile = NULL;

	long unsigned int lineSize = 0;
	char *lineBuffer = NULL;
	unsigned int insArrayIndex = 0;

	assemblyFile = efopen(assemblyFileLocation, "r");

	// Comptage du nombre d'instructions
	while (getline(&lineBuffer, &lineSize, assemblyFile) != -1) // getline alloue dynamiquement un buffer pour la ligne
		g_instructions_count += isInstruction(lineBuffer);

	if (lineBuffer != NULL)
	{
		free(lineBuffer);
		lineBuffer = NULL;
	}

	LOG_DEBUG("Chargement de %d instructions en mémoire", g_instructions_count);
	g_instructions = emalloc(sizeof(Instruction) * g_instructions_count);

	// Chargement des instructions
	rewind(assemblyFile);
	while (getline(&lineBuffer, &lineSize, assemblyFile) != -1)
	{
		Instruction *ins = parseLine(lineBuffer);
		if(ins != NULL)
		{
			g_instructions[insArrayIndex] = ins;
			insArrayIndex++;
		}
	}

	if (lineBuffer != NULL)
	{
		free(lineBuffer);
		lineBuffer = NULL;
	}

	fclose(assemblyFile);
}


Instruction *parseLine(char *line)
{
	char *lPtr;
	char *opcode;
	char *operand;

	while ((*line == ' ') || (*line == '\t'))
		line++;

	if (*line == '#' || *line == '.' || *line == '\n' || *line == '\r')
		return NULL;

	lPtr = line;
	while (*lPtr != '#' && *lPtr != '\0')
	{
		lPtr++;
		if(*lPtr == '(')
			*lPtr = ',';
		else if(*lPtr == ')')
			*lPtr = ' ';
	}

	*(--lPtr) = '\0';
 
	LOG_DEBUG("\tChargement de l'instruction : %s", line);
	opcode = strtok(line, ", ");
	operand = strtok(NULL, "");
	
	for(int i = 0; opcode[i] != '\0'; i++)
		opcode[i] = tolower(opcode[i]);

	if((opcode == NULL || operand == NULL) && strcmp(opcode, "nop") && strcmp(opcode, "syscall"))
		LOG_ERROR("Aucune instruction n'est décodable dans la chaîne \"%s\"", line);

	return instructionLoad(opcode, operand);
}


/**
 * @brief Fonction servant à vérifier si une ligne contient une instruction.
 * 
 * @param line Ligne à vérifier
 * @return bool : 1 si la ligne est une instruction assembleur, 0 sinon 
 */
static char isInstruction(char *line)
{
	while ((*line == ' ') || (*line == '\t')) // Enlever les espaces et tabulations
		line++;

	if (*line == '#' || *line == '.' || *line == '\n' || *line == '\r')
		return 0;
	else
		return 1;
}