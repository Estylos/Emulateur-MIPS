/**
 * @file executions.c
 * @author Nathan BERNARD, Esteban CADIC
 * @brief Programme executant les instructions.
 * Chaque fonction de ce programme contient le comportement attendu pour chaque instruction.
 * @copyright Sous licence MIT
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "executions.h"
#include "util.h"
#include "registers.h"
#include "memory.h"


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void executionAdd(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);
	int32_t res = rs + rt;

	if ((rs > 0 && rt > 0 && res < 0) || (rs < 0 && rt < 0 && res > 0))
		LOG_RUNTIME_ERROR("L'addition des registres $%d (%d) et $%d (%d) dépasse 32 bits (signed)", ins->r.rs, rs, ins->r.rt, rt);

	setRegister(ins->r.rd, res);
	increasePc(1);
}

void executionAddi(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->i.rt, ins->i.rs, ins->i.x);

	int32_t rs = getRegister(ins->i.rs);
	int32_t imm = ins->i.x;
	int32_t res = rs + imm;

	if ((rs > 0 && imm > 0 && res < 0) || (rs < 0 && imm < 0 && res > 0))
		LOG_RUNTIME_ERROR("L'addition du registre $%d (%d) et de l'immédiat %d dépasse 32 bits (signed)", ins->i.rs, rs, imm);

	setRegister(ins->i.rt, res);
	increasePc(1);
}

void executionAnd(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);

	setRegister(ins->r.rd, rs & rt);
	increasePc(1);
}

void executionBeq(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->i.rs, ins->i.rt, ins->i.x);

	int16_t offset = ins->i.x;
	int32_t target_offset = ((int32_t)offset) << 2;
	uint32_t rs = getRegister(ins->i.rs);
	uint32_t rt = getRegister(ins->i.rt);

	increasePc(1);
	if (rs == rt)
		setJumpAtNextIncreasePc(getRegister(REG_PC) + target_offset);
}

void executionBgtz(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d %d\"", ins->name, ins->i.rs, ins->i.x);

	int16_t offset = ins->i.x;
	int32_t target_offset = ((int32_t)offset) << 2;
	int32_t rs = (int32_t)getRegister(ins->i.rs);

	increasePc(1);
	if (rs > 0)
		setJumpAtNextIncreasePc(getRegister(REG_PC) + target_offset);
}

void executionBlez(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d %d\"", ins->name, ins->i.rs, ins->i.x);

	int16_t offset = ins->i.x;
	int32_t target_offset = ((int32_t)offset) << 2;
	int32_t rs = (int32_t)getRegister(ins->i.rs);

	increasePc(1);
	if (rs <= 0)
		setJumpAtNextIncreasePc(getRegister(REG_PC) + target_offset);
}

void executionBne(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->i.rs, ins->i.rt, ins->i.x);

	int16_t offset = ins->i.x;
	int32_t target_offset = ((int32_t)offset) << 2;
	uint32_t rs = getRegister(ins->i.rs);
	uint32_t rt = getRegister(ins->i.rt);

	increasePc(1);
	if (rs != rt)
		setJumpAtNextIncreasePc(getRegister(REG_PC) + target_offset);
}

void executionDiv(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d\"", ins->name, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);

	if (rt == 0)
		LOG_RUNTIME_ERROR("Division par 0");

	setRegister(REG_LO, (int32_t) rs / rt);
	setRegister(REG_HI, (int32_t) rs % rt);

	increasePc(1);
}

void executionJ(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s %d\"", ins->name, ins->j.target);

	uint32_t pc;
	uint32_t jump;

	increasePc(1);
	pc = getRegister(REG_PC);
	jump = (pc & 0xF0000000) | ((ins->j.target << 2) & 0x0FFFFFFF);
	setJumpAtNextIncreasePc(jump);
}

void executionJal(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s %d\"", ins->name, ins->j.target);

	uint32_t jump;
	uint32_t pc = getRegister(REG_PC);

	setRegister(REG_RA, pc + 8);
	increasePc(1);
	pc = getRegister(REG_PC);
	jump = (pc & 0xF0000000) | ((ins->j.target << 2) & 0x0FFFFFFF);
	setJumpAtNextIncreasePc(jump);
}

void executionJr(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d\"", ins->name, ins->r.rs);
	
	uint32_t jump = getRegister(ins->r.rs);
	increasePc(1);
	setJumpAtNextIncreasePc(jump);
}

void executionLui(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d %d\"", ins->name, ins->i.rt, ins->i.x);

	setRegister(ins->i.rt, ins->i.x << 16);
	increasePc(1);
}

void executionLw(const Instruction *ins)
{
	// rs = base
	LOG_DEBUG("Execution de l'instruction \"%s $%d %d($%d)\"", ins->name, ins->i.rt, ins->i.x, ins->i.rs);

	int16_t offset = ins->i.x;
	uint32_t address = getRegister(ins->i.rs) + offset;

	if((address & 0b11) != 0)
		LOG_RUNTIME_ERROR("L'adresse %d (0x%08X) n'est pas alignée sur 32 bits", address, address);

	setRegister(ins->i.rt, getMemory(address));
	increasePc(1);
}

void executionMfhi(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d\"", ins->name, ins->r.rd);

	setRegister(ins->r.rd, getRegister(REG_HI));
	increasePc(1);
}

void executionMflo(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d\"", ins->name, ins->r.rd);

	setRegister(ins->r.rd, getRegister(REG_LO));
	increasePc(1);
}

void executionMult(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d\"", ins->name, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);
	int64_t res = rs*rt;

	setRegister(REG_LO, (int32_t) (res & 0xFFFFFFFF));
	setRegister(REG_HI, (int32_t) (res >> 32));
	increasePc(1);
}

void executionNop(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s\"", ins->name);
	increasePc(1);
}

void executionOr(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);

	setRegister(ins->r.rd, rs | rt);
	increasePc(1);
}

void executionRotr(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->r.rd, ins->r.rt, ins->r.sa);

	uint32_t rt = getRegister(ins->r.rt);
	uint8_t sa = ins->r.sa;

	setRegister(ins->r.rd, (rt >> sa) | (rt << (32 - sa))); // 32 bits rotr
	increasePc(1);
}

void executionSll(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->r.rd, ins->r.rt, ins->r.sa);

	uint32_t rt = getRegister(ins->r.rt);

	setRegister(ins->r.rd, rt << ins->r.sa);
	increasePc(1);
}

void executionSlt(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t l = (int32_t)getRegister(ins->r.rs);
	int32_t h = (int32_t)getRegister(ins->r.rt);

	if (l < h)
		setRegister(ins->r.rd, 1);
	else
		setRegister(ins->r.rd, 0);
		
	increasePc(1);
}

void executionSrl(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d %d\"", ins->name, ins->r.rd, ins->r.rt, ins->r.sa);

	uint32_t rt = getRegister(ins->r.rt);

	setRegister(ins->r.rd, rt >> ins->r.sa);
	increasePc(1);
}

void executionSub(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);
	int32_t res = rs - rt;

	if ((rs < 0 && rt > 0 && res > 0) || (rs > 0 && rt < 0 && res < 0))
		LOG_RUNTIME_ERROR("La soustraction des registres $%d (%d) et $%d (%d) dépasse 32 bits (signed)", ins->r.rs, rs, ins->r.rt, rt);

	setRegister(ins->r.rd, res);
	increasePc(1);
}

void executionSw(const Instruction *ins)
{
	// rs = base
	LOG_DEBUG("Execution de l'instruction \"%s $%d %d($%d)\"", ins->name, ins->i.rt, ins->i.x, ins->i.rs);

	int16_t offset = ins->i.x;
	uint32_t address = getRegister(ins->i.rs) + offset;

	if((address & 0b11) != 0)
		LOG_RUNTIME_ERROR("L'adresse %d (0x%08X) n'est pas alignée sur 32 bits", address, address);

	setMemory(address, getRegister(ins->i.rt));
	increasePc(1);
}

void executionSyscall(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s\"", ins->name);
	increasePc(1);
}

void executionXor(const Instruction *ins)
{
	LOG_DEBUG("Execution de l'instruction \"%s $%d $%d $%d\"", ins->name, ins->r.rd, ins->r.rs, ins->r.rt);

	int32_t rs = getRegister(ins->r.rs);
	int32_t rt = getRegister(ins->r.rt);

	setRegister(ins->r.rd, rs ^ rt);
	increasePc(1);
}