/**
 * @file memory.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du programme simulant la mémoire volatile.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à intialiser la mémoire volatile (manipulé par SW et LW). 
 * 
 */
extern void initMemory(void);

/**
 * @brief Fonction servant à libérer toute la mémoire volatile. 
 * 
 */
extern void freeMemory(void);

/**
 * @brief Fonction servant à récupérer une donnée en mémoire.
 * Renvoie une valeur aléatoire sur 32 bits si aucune donnée n'est présente à l'adresse.
 * 
 * @param address Adresse à laquelle la donnée est présente (sur 32 bits)
 * @return data : Donnée située à l'adresse passée en paramètre. 
 */
extern uint32_t getMemory(const uint32_t address);

/**
 * @brief Fonction servant à sauvegarder une donnée en mémoire.
 * 
 * @param address Adresse à laquelle la donnée doit être sauvegardée.
 * @param val Donnée (sur 32 bits)
 */
extern void setMemory(const uint32_t address, const uint32_t val);

/**
 * @brief Fonction servant à afficher tout le contenu de la mémoire.
 * 
 * @param stream Pointeur vers le flux sur lequel on veut produire l'affichage
 */
extern void printMemory(FILE *stream);


#endif