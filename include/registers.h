/**
 * @file registers.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du programme simulant les registres du processeur.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>


/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

/** 
 * @addtogroup REGISTERS
 * Alias de tous les registres du processeur.
 * @{
 */
#define REG_ZERO 0
#define REG_AT 1
#define REG_V0 2
#define REG_V1 3
#define REG_A0 4
#define REG_A1 5
#define REG_A2 6
#define REG_A3 7
#define REG_T0 8
#define REG_T1 9
#define REG_T2 10
#define REG_T3 11
#define REG_T4 12
#define REG_T5 13
#define REG_T6 14
#define REG_T7 15
#define REG_S0 16
#define REG_S1 17
#define REG_S2 18
#define REG_S3 19
#define REG_S4 20
#define REG_S5 21
#define REG_S6 22
#define REG_S7 23
#define REG_T8 24
#define REG_T9 25
#define REG_K0 26
#define REG_K1 27
#define REG_GP 28
#define REG_SP 29
#define REG_FP 30
#define REG_RA 31
#define REG_PC 32
#define REG_HI 33
#define REG_LO 34
/** @} */


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à intialiser tous les registres.
 * 
 */
extern void initRegisters(void);

/**
 * @brief Fonction servant à récupérer la donnée d'un registre.
 * 
 * @param regNumber Numero du registre
 * @return data : Donnée contenue dans le registre (sur 32 bits) 
 */
extern uint32_t getRegister(const unsigned char regNumber);

/**
 * @brief Fonction servant à sauvegarder une donnée dans un registre.
 * 
 * @param regNumber Registre dans lequelle la donnée doit être sauvegardée.
 * @param val Donnée (sur 32 bits)
 */
extern void setRegister(const unsigned char regNumber, const uint32_t val);

/**
 * @brief Fonction servant à augmenter ou baisser le PC d'un nombre d'instructions.
 * 
 * @param instructionsNb Nombre d'instructions (signé)
 */
extern void increasePc(const int instructionsNb); 

/**
 * @brief Fonction servant à récupérer la valeur du PC en nombre d'instructions (PC/4).
 * 
 * @return pc : Valeur du PC/4
 */
extern uint32_t getPcInstructionsNb(void); 

/**
 * @brief Fonction servant à indiquer un saut après le delay slot.
 * 
 * @param address Adresse absolue à laquelle sauter après le delay slot
 */
extern void setJumpAtNextIncreasePc(const uint32_t address);

/**
 * @brief Fonction servant à afficher tout le contenu des registres.
 * 
 * @param stream Pointeur vers le flux sur lequel on veut produire l'affichage
 */
extern void printRegister(FILE *stream);


#endif