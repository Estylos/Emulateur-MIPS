/**
 * @file instructions.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme chargeant les instructions en mémoire.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "instructions.h"
#include "executions.h"
#include "util.h"


/*------------------------------------------------------------------------------
	CONSTANTS
------------------------------------------------------------------------------*/

/** 
 * @addtogroup GENERIC_INSTRUCTIONS
 * Liste de toutes les instructions génériques
 * @{
 */
const Instruction *g_mips_def_instructions[DEF_INSTRUCTIONS_COUNT];
const Instruction mips_add = {.name = "add", .opcode = 0b100000, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionAdd)};
const Instruction mips_addi = {.name = "addi", .opcode = 0b001000, .typeCode = I_TYPE, .formatCode = IF_TSI, .execute = (&executionAddi)};
const Instruction mips_and = {.name = "and", .opcode = 0b100100, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionAnd)};
const Instruction mips_beq = {.name = "beq", .opcode = 0b000100, .typeCode = I_TYPE, .formatCode = IF_STO, .execute = (&executionBeq)};
const Instruction mips_bgtz = {.name = "bgtz", .opcode = 0b000111, .typeCode = I_TYPE, .formatCode = IF_SO, .execute = (&executionBgtz)};
const Instruction mips_blez = {.name = "blez", .opcode = 0b000110, .typeCode = I_TYPE, .formatCode = IF_SO, .execute = (&executionBlez)};
const Instruction mips_bne = {.name = "bne", .opcode = 0b000101, .typeCode = I_TYPE, .formatCode = IF_STO, .execute = (&executionBne)};
const Instruction mips_div = {.name = "div", .opcode = 0b011010, .typeCode = R_TYPE, .formatCode = RF_ST, .execute = (&executionDiv)};
const Instruction mips_j = {.name = "j", .opcode = 0b000010, .typeCode = J_TYPE, .formatCode = JF_T, .execute = (&executionJ)};
const Instruction mips_jal = {.name = "jal", .opcode = 0b000011, .typeCode = J_TYPE, .formatCode = JF_T, .execute = (&executionJal)};
const Instruction mips_jr = {.name = "jr", .opcode = 0b001000, .typeCode = R_TYPE, .formatCode = RF_S, .execute = (&executionJr)};
const Instruction mips_lui = {.name = "lui", .opcode = 0b001111, .typeCode = I_TYPE, .formatCode = IF_TI, .execute = (&executionLui)};
const Instruction mips_lw = {.name = "lw", .opcode = 0b100011, .typeCode = I_TYPE, .formatCode = IF_TOB, .execute = (&executionLw)};
const Instruction mips_mfhi = {.name = "mfhi", .opcode = 0b010000, .typeCode = R_TYPE, .formatCode = RF_D, .execute = (&executionMfhi)};
const Instruction mips_mflo = {.name = "mflo", .opcode = 0b010010, .typeCode = R_TYPE, .formatCode = RF_D, .execute = (&executionMflo)};
const Instruction mips_mult = {.name = "mult", .opcode = 0b011000, .typeCode = R_TYPE, .formatCode = RF_ST, .execute = (&executionMult)};
const Instruction mips_nop = {.name = "nop", .opcode = 0b000000, .typeCode = R_TYPE, .formatCode = RF_0, .execute = (&executionNop)};
const Instruction mips_or = {.name = "or", .opcode = 0b100101, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionOr)};
const Instruction mips_rotr = {.name = "rotr", .opcode = 0b000010, .typeCode = R_TYPE, .formatCode = RF_1DTA, .execute = (&executionRotr)};
const Instruction mips_sll = {.name = "sll", .opcode = 0b000000, .typeCode = R_TYPE, .formatCode = RF_DTA, .execute = (&executionSll)};
const Instruction mips_slt = {.name = "slt", .opcode = 0b101010, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionSlt)};
const Instruction mips_srl = {.name = "srl", .opcode = 0b000010, .typeCode = R_TYPE, .formatCode = RF_DTA, .execute = (&executionSrl)};
const Instruction mips_sub = {.name = "sub", .opcode = 0b100010, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionSub)};
const Instruction mips_sw = {.name = "sw", .opcode = 0b101011, .typeCode = I_TYPE, .formatCode = IF_TOB, .execute = (&executionSw)};
const Instruction mips_syscall = {.name = "syscall", .opcode = 0b001100, .typeCode = R_TYPE, .formatCode = RF_0, .execute = (&executionSyscall)};
const Instruction mips_xor = {.name = "xor", .opcode = 0b100110, .typeCode = R_TYPE, .formatCode = RF_DST, .execute = (&executionXor)};
/** @} */

/**
 * @brief Types d'opérandes existantes (registre, entier sur 16 bits, entier sur 32 bits).
 *
 */
enum OperandType { OT_REG, OT_X_16, OT_X_32 };

/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static Instruction *rTypeLoad(const Instruction *patern, char *operand);
static Instruction *iTypeLoad(const Instruction *patern, char *operand);
static Instruction *jTypeLoad(const Instruction *patern, char *operand);
static int operandToNum(char *operand, enum OperandType operandType);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void instructionsInit(void)
{
	LOG_DEBUG("Chargement des instructions génériques en mémoire");
	g_mips_def_instructions[0] = &mips_add;
	g_mips_def_instructions[1] = &mips_addi;
	g_mips_def_instructions[2] = &mips_and;
	g_mips_def_instructions[3] = &mips_beq;
	g_mips_def_instructions[4] = &mips_bgtz;
	g_mips_def_instructions[5] = &mips_blez;
	g_mips_def_instructions[6] = &mips_bne;
	g_mips_def_instructions[7] = &mips_div;
	g_mips_def_instructions[8] = &mips_j;
	g_mips_def_instructions[9] = &mips_jal;
	g_mips_def_instructions[10] = &mips_jr;
	g_mips_def_instructions[11] = &mips_lui;
	g_mips_def_instructions[12] = &mips_lw;
	g_mips_def_instructions[13] = &mips_mfhi;
	g_mips_def_instructions[14] = &mips_mflo;
	g_mips_def_instructions[15] = &mips_mult;
	g_mips_def_instructions[16] = &mips_nop;
	g_mips_def_instructions[17] = &mips_or;
	g_mips_def_instructions[18] = &mips_rotr;
	g_mips_def_instructions[19] = &mips_sll;
	g_mips_def_instructions[20] = &mips_slt;
	g_mips_def_instructions[21] = &mips_srl;
	g_mips_def_instructions[22] = &mips_sub;
	g_mips_def_instructions[23] = &mips_sw;
	g_mips_def_instructions[24] = &mips_syscall;
	g_mips_def_instructions[25] = &mips_xor;
}


Instruction *instructionLoad(char *opcode, char *operand)
{
	char err = 1;
	Instruction *ins;

	for(int i = 0; i < DEF_INSTRUCTIONS_COUNT; i++)
	{
		if(strcmp(g_mips_def_instructions[i]->name, opcode) == 0)
		{
			err = 0;
			switch (g_mips_def_instructions[i]->typeCode)
			{
			case R_TYPE:
				LOG_DEBUG("\t\tType de %s : R", opcode);
				ins = rTypeLoad(g_mips_def_instructions[i], operand);
				break;
			case I_TYPE:
				LOG_DEBUG("\t\tType de %s : I", opcode);
				ins = iTypeLoad(g_mips_def_instructions[i], operand);
				break;
			case J_TYPE:
				LOG_DEBUG("\t\tType de %s : J", opcode);
				ins = jTypeLoad(g_mips_def_instructions[i], operand);
				break;
			default:
				err = 1;
				break;
			}
		}
	}

	if(err || ins == NULL)
	{
		LOG_ERROR("Opcode \"%s\" non reconnu", opcode);
		return NULL;
	}
	else
	{
#ifdef __DEBUG__
		char *hexIns = instructionToHex(ins);
		LOG_DEBUG("\t\tValeur hexa : 0x%s", hexIns);
		free(hexIns);
#endif
		return ins;
	}
}

char *instructionToHex(Instruction *ins)
{
	char *hex = emalloc(sizeof(char) * 9);
	int assembled = 0;

	if(ins->typeCode == R_TYPE)
	{
		assembled += ins->opcode & 0x3F;
		assembled += (ins->r.sa & 0x1F) << 6;
		assembled += (ins->r.rd & 0x1F) << 11;
		assembled += (ins->r.rt & 0x1F) << 16;
		assembled += (ins->r.rs & 0x1F) << 21;
	}
	else if(ins->typeCode == I_TYPE)
	{
		assembled += ins->i.x & 0xFFFF;
		assembled += (ins->i.rt & 0x1F) << 16;
		assembled += (ins->i.rs & 0x1F) << 21;
		assembled += (ins->opcode& 0x3F) << 26;
	}
	else if(ins->typeCode == J_TYPE)
	{
		assembled += ins->j.target & 0x3FFFFFF;
		assembled += (ins->opcode & 0x3F) << 26;
	}

	sprintf(hex, "%08X", assembled);

	return hex;
}


void freeAllInstructions(void)
{
	LOG_DEBUG("Libération des instructions en mémoire");
	if(g_instructions == NULL)
		return;
	
	for(unsigned int i = 0; i < g_instructions_count; i++)
		free(g_instructions[i]);

	free(g_instructions);
	g_instructions = NULL;
}


/**
 * @brief Fonction servant à charger une instruction de type R en mémoire.
 * 
 * @param patern Instruction générique de base
 * @param operand Opérandes sous la forme d'une chaîne de caractères
 * @return ins : Pointeur vers l'instruction chargée en mémoire
 */
static Instruction *rTypeLoad(const Instruction *patern, char *operand)
{
	Instruction *ins = emalloc(sizeof(Instruction));
	memcpy(ins, patern, sizeof(Instruction));
	
	ins->r.rs = 0;
	ins->r.rt = 0;
	ins->r.rd = 0;
	ins->r.sa = 0;

	enum Format f = ins->formatCode;

	// SPECIAL
	if(f == RF_0)
		return ins;
	else if(f == RF_1DTA)
		ins->r.rs = 1;

	char *operandTmp = strdup(operand);

	// 1ER ARGUMENT
	if(f == RF_S || f == RF_ST)
		ins->r.rs = operandToNum(estrtok(operandTmp, ", "), OT_REG);
	else if(f == RF_D || f == RF_DST || f == RF_DTA ||  f == RF_1DTA)
		ins->r.rd = operandToNum(estrtok(operandTmp, ", "), OT_REG);

	// 2E ARGUMENT                 
	if(f == RF_DST)
		ins->r.rs = operandToNum(estrtok(NULL, ", "), OT_REG);
	else if(f == RF_ST)
		ins->r.rt = operandToNum(estrtok(NULL, ", "), OT_REG);
	else if(f == RF_DTA || f == RF_1DTA)
		ins->r.rt = operandToNum(estrtok(NULL, ", "), OT_REG);

	// 3E ARGUMENT
	if(f == RF_DST)
		ins->r.rt = operandToNum(estrtok(NULL, ", "), OT_REG);
	else if(f == RF_DTA || f == RF_1DTA)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, 0, 0x1F, "Operande sa \"%d\" depasse 5 bits (unsigned)", val);
		ins->r.sa = val;
	}

	if(strtok(NULL, ", ") != NULL)
		LOG_WARN("Surcharge d'opérandes sur l'instruction : %s %s", ins->name, operand);

	free(operandTmp);

	LOG_DEBUG("\t\trs = %d ; rt = %d ; rd = %d ; sa = %d", ins->r.rs, ins->r.rt, ins->r.rd, ins->r.sa);
	return ins;
}


/**
 * @brief Fonction servant à charger une instruction de type I en mémoire.
 * NB : Le passage de "rt, offset(base)" doit se faire ainsi : "rt, offset, base".
 * 
 * @param patern Instruction générique de base
 * @param operand Opérandes sous la forme d'une chaîne de caractères
 * @return ins : Pointeur vers l'instruction chargée en mémoire
 */
static Instruction *iTypeLoad(const Instruction *patern, char *operand)
{
	Instruction *ins = emalloc(sizeof(Instruction));
	memcpy(ins, patern, sizeof(Instruction));
	
	ins->i.rs = 0;
	ins->i.rt = 0;
	ins->i.x = 0;

	enum Format f = ins->formatCode;
	char *operandTmp = strdup(operand);

	// 1ER ARGUMENT
	if(f == IF_STO || f == IF_SO)
		ins->i.rs = operandToNum(estrtok(operandTmp, ", "), OT_REG);
	else if(f == IF_TI || f == IF_TOB || f == IF_TSI)
		ins->i.rt = operandToNum(estrtok(operandTmp, ", "), OT_REG);
	
	// 2E ARGUMENT
	if(f == IF_STO)
		ins->i.rt = operandToNum(estrtok(NULL, ", "), OT_REG);
	else if(f == IF_TSI)
		ins->i.rs = operandToNum(estrtok(NULL, ", "), OT_REG);
	else if(f == IF_TOB)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, INT16_MIN, INT16_MAX, "Operande offset \"%d\" depasse 16 bits (signed)", val);
		ins->i.x = val;
	}
	else if(f == IF_TI)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, 0, UINT16_MAX, "Operande immediate \"%d\" depasse 16 bits (unsigned)", val);
		ins->i.x = val;
	}
	else if(f == IF_SO)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, INT16_MIN, INT16_MAX, "Operande offset \"%d\" depasse 16 bits (signed)");
		ins->i.x = val;
	}

	// 3E ARGUMENT
	if(f == IF_TSI)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, INT16_MIN, INT16_MAX, "Operande immediate \"%d\" depasse 16 bits (signed)", val);
		ins->i.x = val;
	}
	else if(f == IF_STO)
	{
		int val = operandToNum(estrtok(NULL, ", "), OT_X_16);
		LOG_ERROR_NB_INTERVAL(val, INT16_MIN, INT16_MAX, "Operande offset \"%d\" depasse 16 bits (signed)");
		ins->i.x = val;
	}
	else if(f == IF_TOB)
		ins->i.rs = operandToNum(estrtok(NULL, ", "), OT_REG);

	if(strtok(NULL, ", ") != NULL)
		LOG_WARN("Surcharge d'opérandes sur l'instruction : %s %s", ins->name, operand);

	free(operandTmp);

	LOG_DEBUG("\t\trs = %d ; rt = %d ; x = %d", ins->i.rs, ins->i.rt, ins->i.x);
	return ins;
}


/**
 * @brief Fonction servant à charger une instruction de type J en mémoire.
 * 
 * @param patern Instruction générique de base
 * @param operand Opérandes sous la forme d'une chaîne de caractères
 * @return ins : Pointeur vers l'instruction chargée en mémoire
 */
static Instruction *jTypeLoad(const Instruction *patern, char *operand)
{
	Instruction *ins = emalloc(sizeof(Instruction));
	memcpy(ins, patern, sizeof(Instruction));
	
	ins->j.target = 0;

	enum Format f = ins->formatCode;

	if(f == JF_T)
		ins->j.target = (operandToNum(operand, OT_X_32) & 0x3FFFFFF); // operand AND 26 bits mask

	LOG_DEBUG("\t\ttarget = %d", ins->j.target);
	return ins;
}


/**
 * @brief Fonction servant à convertir une opérande litérale en entier.
 * 
 * @param operand Opérande sous la forme d'une chaîne de caractères
 * @param operandType Type de l'opérande (registre ou immediate/offest)
 * @return val : Valeur entière à sauvegarder dans l'instruction
 */
static int operandToNum(char *operand, enum OperandType operandType)
{
	int val = -1;

	if(*operand == '$') // REG
	{
		if(operandType == OT_X_16 || operandType == OT_X_32)
			LOG_WARN("Opérande \"%s\" est de type registre alors qu'elle devrait être de type immediate/offset", operand);
		operand++;
		if(isdigit(*operand)) // $6, $10 -> registre direct, on renvoie le nombre
		{
			val = atoi(operand);
			LOG_ERROR_NB_INTERVAL(val, 0, 31, "Registre \"$%d\" hors limite", val);
		} 
		else // $t0, $ra -> Convertir en nombre
		{
			if(!strcmp(operand, "zero"))
				val = 0;
			else if(!strcmp(operand, "at"))
				val = 1;
			else if(!strcmp(operand, "gp"))
				val = 28;
			else if(!strcmp(operand, "sp"))
				val = 29;
			else if(!strcmp(operand, "fp"))
				val = 30;
			else if(!strcmp(operand, "ra"))
				val = 31;
			else if(*operand == 'v')
			{
				operand++;
				val = atoi(operand);
				LOG_ERROR_NB_INTERVAL(val, 0, 1, "Registre \"$v%d\" hors limite", val);
				val += 2;
			}
			else if(*operand == 'a')
			{
				operand++;
				val = atoi(operand);
				LOG_ERROR_NB_INTERVAL(val, 0, 3, "Registre \"$a%d\" hors limite", val);
				val += 4;
			}
			else if(*operand == 't')
			{
				operand++;
				val = atoi(operand);
				LOG_ERROR_NB_INTERVAL(val, 0, 9, "Registre \"$t%d\" hors limite", val);
				if(val <= 7)
					val += 8;
				else
					val += 16;
			}
			else if(*operand == 's')
			{
				operand++;
				val = atoi(operand);
				LOG_ERROR_NB_INTERVAL(val, 0, 7, "Registre \"$s%d\" hors limite", val);
				val += 16;
			}
			else if(*operand == 'k')
			{
				operand++;
				val = atoi(operand);
				LOG_ERROR_NB_INTERVAL(val, 0, 1, "Registre \"$k%d\" hors limite", val);
				val += 26;
			}
			else
				LOG_ERROR("Opérande \"%s\" non reconnue", --operand);
		}        
	}
	else // IMM_OFF
	{
		if(operandType == OT_REG)
			LOG_WARN("Opérande \"%s\" est de type immediate/offset alors qu'elle devrait être de type registre", operand);
		long longVal = strtol(operand, NULL, 10);
		if(longVal < 0)
		{
			if(operandType == OT_X_32 && (longVal > INT32_MAX || longVal < INT32_MIN))
				LOG_ERROR("Opérande \"%s\" depasse 32 bits (signed)", operand);
			else if(operandType == OT_X_16 && (longVal > INT16_MAX || longVal < INT16_MIN))
				LOG_ERROR("Opérande \"%s\" depasse 16 bits (signed)", operand);
		}
		else
		{
			if(operandType == OT_X_32 && longVal > UINT32_MAX)
				LOG_ERROR("Opérande \"%s\" depasse 32 bits (unsigned)", operand);
			else if(operandType == OT_X_16 && longVal > UINT16_MAX)
				LOG_ERROR("Opérande \"%s\" depasse 16 bits (unsigned)", operand);
		}

		val = longVal;
	}
	return val;
}
