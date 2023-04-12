/**
 * @file automatic.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme gérant le mode fichier automatique et le mode fichier pas à pas.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "automatic.h"
#include "parser.h"
#include "instructions.h"
#include "registers.h"
#include "memory.h"


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void automaticByStep(char *assemblyFileLocation)
{
	LOG_DEBUG("Mode pas à pas");
	FILE *assemblyFile = efopen(assemblyFileLocation, "r");

	printf("Chargement des instructions en mémoire...\n");
	parseAssemblyFile(assemblyFileLocation);

	printf("Execution des instructions pas à pas...\n");
	unsigned int pcIndexTab = getPcInstructionsNb();
	while(pcIndexTab < g_instructions_count)
	{	
		printf(ANSI_CODE_BOLD "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" ANSI_CODE_RESET);
		
		char *hexaIns = instructionToHex(g_instructions[pcIndexTab]);
		printf("Execution de l'instruction [PC/4 = %d] 0x%s (nom : %s) ", pcIndexTab, hexaIns, g_instructions[pcIndexTab]->name);
		printf(ANSI_CODE_GREY "(essayez le mode debug \"-D__DEBUG__\" pour plus d'informations)" ANSI_CODE_RESET "\n");
		free(hexaIns);

		LOG_DEBUG("Valeur du PC (/4) : %d", pcIndexTab);
		g_instructions[pcIndexTab]->execute(g_instructions[pcIndexTab]);

		printRegister(stdout);
		printMemory(stdout);

		pcIndexTab = getPcInstructionsNb();
		
		printf("Appuyez sur entrée pour continuer...\n");
		getchar();
	}
	
	printf("Fin de l'execution\n");

	fclose(assemblyFile);
}

void automatic(char *assemblyFileLocation, char *assembledFileLocation, char *finalStateFileLocation)
{
	LOG_DEBUG("Mode automatique");
	FILE *assembledFile;
	FILE *finalStateFile;

	parseAssemblyFile(assemblyFileLocation);

	LOG_DEBUG("Sauvegarde des instructions assemblées");
	assembledFile = efopen(assembledFileLocation, "w");

	for(unsigned int i = 0; i < g_instructions_count; i++)
	{
		char *hexaIns = instructionToHex(g_instructions[i]);
		fprintf(assembledFile, "%s\n", hexaIns);
		free(hexaIns);
	}

	unsigned int pcIndexTab = getPcInstructionsNb();
	while(pcIndexTab < g_instructions_count)
	{	
		LOG_DEBUG("Valeur du PC (/4) : %d", pcIndexTab);
		g_instructions[pcIndexTab]->execute(g_instructions[pcIndexTab]);
		pcIndexTab = getPcInstructionsNb();
	}

	LOG_DEBUG("Fin de l'execution");

	LOG_DEBUG("Sauvegarde de l'état final des registres");
	finalStateFile = efopen(finalStateFileLocation, "w");
	printRegister(finalStateFile);

	fclose(assembledFile);
	fclose(finalStateFile);
}