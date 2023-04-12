/**
 * @file executions.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du programme executant les instructions.
 * Chaque fonction de ce programme contient le comportement attendu pour chaque instruction.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __EXECUTIONS_H__
#define __EXECUTIONS_H__


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

extern void executionAdd(const Instruction *ins);
extern void executionAddi(const Instruction *ins);
extern void executionAnd(const Instruction *ins);
extern void executionBeq(const Instruction *ins);
extern void executionBgtz(const Instruction *ins);
extern void executionBlez(const Instruction *ins);
extern void executionBne(const Instruction *ins);
extern void executionDiv(const Instruction *ins);
extern void executionJ(const Instruction *ins);
extern void executionJal(const Instruction *ins);
extern void executionJr(const Instruction *ins);
extern void executionLui(const Instruction *ins);
extern void executionLw(const Instruction *ins);
extern void executionMfhi(const Instruction *ins);
extern void executionMflo(const Instruction *ins);
extern void executionMult(const Instruction *ins);
extern void executionNop(const Instruction *ins);
extern void executionOr(const Instruction *ins);
extern void executionRotr(const Instruction *ins);
extern void executionSll(const Instruction *ins);
extern void executionSlt(const Instruction *ins);
extern void executionSrl(const Instruction *ins);
extern void executionSub(const Instruction *ins);
extern void executionSw(const Instruction *ins);
extern void executionSyscall(const Instruction *ins);
extern void executionXor(const Instruction *ins);


#endif