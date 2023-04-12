/**
 * @file instructions.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du programme chargeant les instructions en mémoire.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__


/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

/**
 * @brief Nombre d'instructions génériques.
 *
 */
#define DEF_INSTRUCTIONS_COUNT 26


/*------------------------------------------------------------------------------
	ENUM DEFINITIONS
------------------------------------------------------------------------------*/

/**
 * @brief Enumération des différents types d'instructions.
 *
 */
enum Type
{
	R_TYPE,
	I_TYPE,
	J_TYPE
};

/**
 * @brief Enumération des différents formats des opérandes.
 *
 */
enum Format
{
	RF_DST, RF_ST, RF_S, RF_D, RF_0, RF_1DTA, RF_DTA,
	IF_TSI, IF_STO, IF_SO, IF_TI, IF_TOB,
	JF_T
};


/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/

/**
 * @brief Structure représentant les opérandes d'instruction de type R.
 *
 */
typedef struct
{
	unsigned char rs : 5;
	unsigned char rt : 5;
	unsigned char rd : 5;
	unsigned char sa : 5;
} RType;

/**
 * @brief Structure représentant les opérandes d'instruction de type I.
 *
 */
typedef struct
{
	unsigned char rs : 5;
	unsigned char rt : 5;
	int x : 16; /**< Valeur immédiate ou offset (signé) */
} IType;

/**
 * @brief Structure représentant les opérandes d'instruction de type J.
 *
 */
typedef struct
{
	unsigned int target : 26;
} JType;

/**
 * @brief Structure représentant une instruction.
 *
 */
typedef struct instruction
{
	char *name;                     			/**< Nom de l'instruction */
	const enum Type typeCode;       			/**< Type de l'instruction (R / I / J) */
	const enum Format formatCode;  				/**< Format des opérandes de l'instruction */
	unsigned const char opcode : 6; 			/**< Opcode */
	void (*execute)(const struct instruction *);/**< Pointeur de fonction exécutant l'instruction */
	/**
	 * @brief Union stockant les opérandes selon le type.
	 */
	union
	{
		RType r; /**< Opérandes d'instruction de type R */
		IType i; /**< Opérandes d'instruction de type I */
		JType j; /**< Opérandes d'instruction de type J */
	};
} Instruction;


/*------------------------------------------------------------------------------
	GLOBAL VARIABLES
------------------------------------------------------------------------------*/

/**
 * @brief Variable globale contenant toutes les instructions génériques de la documentation MIPS.
 *
 */
extern const Instruction *g_mips_def_instructions[DEF_INSTRUCTIONS_COUNT];

/**
 * @brief Variable globale contenant toutes les instructions du programme en cours d'éxecution.
 *
 */
extern Instruction **g_instructions;

/**
 * @brief Variable globale contenant le nombre d'instructions du programme en cours d'éxecution.
 *
 */
extern unsigned int g_instructions_count;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à charger en mémoire toutes les instructions génériques.
 *
 */
extern void instructionsInit(void);

/**
 * @brief Fonction servant à charger une instruction en mémoire.
 * Déclanche une erreur si l'instruction est invalide.
 * 
 * @param opcode Nom de l'instruction
 * @param operand Opérandes sous la forme d'une chaîne de caractères
 * @return ins : Pointeur vers l'instruction chargée en mémoire
 */
extern Instruction *instructionLoad(char *opcode, char *operand);

/**
 * @brief Fonction servant à traduire une instruction en une chaîne de caractères hexadécimale de 32 bits.
 * NE PAS OUBLIER DE LIBERER LA MEMOIRE.
 * 
 * @param ins Instruction
 * @return hexa : Pointeur vers la chaîne de caractères créée en mémoire
 */
extern char *instructionToHex(Instruction *ins);

/**
 * @brief Fonction servant à libérer toutes les instructions contenues dans g_instructions
 *
 */
extern void freeAllInstructions(void);


#endif