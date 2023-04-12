/**
 * @file main.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme principal de l'émulateur.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <string.h>
#include "automatic.h"
#include "interactive.h"
#include "instructions.h"
#include "memory.h"
#include "registers.h"
#include "util.h"


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction d'entrée du programme.
 * 
 * @param argc Nombre d'arguments d'éxecution
 * @param argv Tableau des arguments d'éxecution
 * @return Etat de sortie du programme
 */
int main(int argc, char **argv)
{
#ifdef __NO_CRASH_ON_ERROR__
	LOG_WARN(ANSI_CODE_BG_RED ANSI_CODE_WHITE ANSI_CODE_BOLD
			"Constante __NO_CRASH_ON_ERROR__ définit. Pas de crash lors des erreurs d'assemblages et d'exécution ! Peut générer un comportement indéfini !"
			ANSI_CODE_RESET);
#endif

	instructionsInit();
	initMemory();
	initRegisters();

	if (argc == 1) // Mode interactif
	{
		interactive();
	}

	else if (argc == 3) // Mode fichier pas à pas
	{
		if (strcmp(argv[2], "-pas") != 0)
			LOG_ERROR("Argument \"%s\" invalide", argv[2]);
		automaticByStep(argv[1]);
	}

	else if (argc == 4) // Mode fichier
	{
		automatic(argv[1], argv[2], argv[3]);
	}

	else
	{
		LOG_WARN("Nombre d'arguments invalide...");
	}

	LOG_DEBUG("Libération de la mémoire...");
	freeAllInstructions();
	freeMemory();
	
	LOG_DEBUG("Terminé sans erreur");

	return 0;
}
