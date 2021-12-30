#include "Phase3.h"
#include "Phase2.h"
#include <stdlib.h>
#include "ArrayList.h"
#include "Instruction.h"
#include "InstructionFactory.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 

//Written By: Cory Freres

void translate_instructions(struct ArrayList *tals, uint32_t machineCode[]) {
    struct Instruction inst;
    int32_t opcode = 0;
    int32_t rs =0;
    int32_t rt = 0;
    int32_t rd = 0;
    int32_t shamt = 0;
    int32_t funct = 0;
    int32_t imm = 0;
    
    for (int i = 0; i < size(tals); i++){
        inst = get(tals, i);
        if (inst.instruction_id == addiu){
            opcode = 9;
            rt = inst.rt;
            rs = inst.rs;
            imm = inst.immediate;
            shamt = 0;
            funct = 0;
            rd = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | imm);
        }
        else if (inst.instruction_id == addu){
            opcode = 0;
            rd = inst.rd;
            rs = inst.rs;
            rt = inst.rt;
            imm = inst.immediate;
            shamt = inst.shift_amount;
            funct = 33;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct);
        }
        else if (inst.instruction_id == sll){
            opcode = 0;
            rd = inst.rd;
            rs = inst.rs;
            rt = inst.rt;
            imm = 0;
            shamt = inst.shift_amount;
            funct = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct);
        }
        else if (inst.instruction_id == or){
            opcode = 0;
            rd = inst.rd;
            rs = inst.rs;
            rt = inst.rt;
            imm = 0;
            shamt = inst.shift_amount;
            funct = 37;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct);
        }
        else if (inst.instruction_id == beq){
            opcode = 4;
            rt = inst.rt;
            rs = inst.rs;
            imm = inst.immediate;
            shamt = 0;
            funct = 0;
            rd = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | imm);
        }
        else if (inst.instruction_id == bne){
            opcode = 5;
            rt = inst.rt;
            rs = inst.rs;
            imm = inst.immediate;
            shamt = 0;
            funct = 0;
            rd = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | imm);
        }
        else if (inst.instruction_id == slt){
            opcode = 0;
            rd = inst.rd;
            rs = inst.rs;
            rt = inst.rt;
            imm = 0;
            shamt = inst.shift_amount;
            funct = 42;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct);
        }
        else if (inst.instruction_id == lui){
            opcode = 15;
            rt = inst.rt;
            rs = inst.rs;
            imm = inst.immediate;
            shamt = 0;
            funct = 0;
            rd = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | imm);
        }
        else if (inst.instruction_id == ori){
            opcode = 13;
            rt = inst.rt;
            rs = inst.rs;
            imm = inst.immediate;
            shamt = 0;
            funct = 0;
            rd = 0;
            machineCode[i] = ((opcode << 26) | (rs << 21) | (rt << 16) | imm);
        }
        
    }

}
