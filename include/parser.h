/**
 * @file parser.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du parseur de fichiers source assembleur.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include "instructions.h"


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à charger un fichier source assembleur en mémoire.
 * 
 * @param assemblyFileLocation Chemin d'accès du fichier source assebleur
 */
extern void parseAssemblyFile(char *assemblyFileLocation);

/**
 * @brief Fonction servant à parser une ligne. 
 * Elle s'occupe d'isoler l'instruction et d'extraire l'opcode et l'opérande pour la charger en mémoire avec instructionLoad().
 * 
 * @param line Ligne à parser
 * @return ins : Pointeur vers l'instruction chargée en mémoire. NULL si la ligne ne contient pas d'instruction
 */
extern Instruction *parseLine(char *line);


#endif