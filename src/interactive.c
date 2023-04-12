/**
 * @file interactive.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme gérant le monde interactif.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "interactive.h"
#include "parser.h"
#include "registers.h"
#include "memory.h"


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void interactive(void)
{
	LOG_DEBUG("Mode interactif");
	LOG_WARN(ANSI_CODE_MAGENTA "JUMPS ET BRANCH NON FONCTIONNELS DANS CE MODE !" ANSI_CODE_RESET);

	char *line = NULL;
	size_t len = 0;
	ssize_t lineSize = 0;

	printf("Entrez une instruction : ");
	lineSize = getline(&line, &len, stdin);
	if (lineSize == -1)
		LOG_ERROR("getline return -1");

	while (strcmp(line, "exit\n") && strcmp(line, "EXIT\n"))
	{
		Instruction *ins = parseLine(line);
		if(ins != NULL)
		{
			char *hexaIns = instructionToHex(ins);
			printf("Execution de l'instruction 0x%s (nom : %s) ", hexaIns, ins->name);
			printf(ANSI_CODE_GREY "(essayez le mode debug \"-D__DEBUG__\" pour plus d'informations)" ANSI_CODE_RESET "\n");
			free(hexaIns);

			ins->execute(ins);
			free(ins);

			printRegister(stdout);
			printMemory(stdout);
		}

		printf(ANSI_CODE_BOLD "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" ANSI_CODE_RESET);
		printf("Entrez une instruction : ");
		lineSize = getline(&line, &len, stdin);
		if (lineSize == -1)
			LOG_ERROR("getline return -1");
	}

	printf("Fin de l'execution\n");
	free(line);
}