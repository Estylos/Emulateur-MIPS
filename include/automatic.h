/**
 * @file automatic.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En-tête du programme gérant le mode fichier automatique et le mode fichier pas à pas.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __AUTOMATIC_H__
#define __AUTOMATIC_H__


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à la gestion du mode fichier en exécution pas à pas.
 * 
 * @param assemblyFileLocation Chemin d'accès du fichier source assembleur.
 */
extern void automaticByStep(char *assemblyFileLocation);

/**
 * @brief Fonction servant à la gestion du mode fichier en exécution automatique.
 * 
 * @param assemblyFileLocation Chemin d'accès du fichier source assembleur
 * @param assembledFileLocation Chemin d'accès du fichier dans lequel sauvegarder les instructions assemblées
 * @param finalStateFileLocation Chemin d'accès du fichier dans lequel sauvegarder l'état final du programme
 */
extern void automatic(char *assemblyFileLocation, char *assembledFileLocation, char *finalStateFileLocation);


#endif