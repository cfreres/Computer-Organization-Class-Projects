#include <assert.h>
#include <stdlib.h>
#include "Instruction.h"
#include "InstructionFactory.h"
#include "ArrayList.h"
#include "Phase1.h"
#include <string.h>

//Written By: Cory Freres

void mal_to_tal(struct ArrayList *mals, struct ArrayList *tals) {
    struct Instruction i;
    
    for (int k = 0; k < size(mals); k++){
    i = get(mals, k);
    
    if (i.instruction_id == addiu && (i.immediate > 0x00007fff || i.immediate < 0xffff8001)){
        struct Instruction addiuSet[3] = {
        CreateLui(1, (i.immediate >> 16) & 0xffffffff),
        CreateOri(1, 1, (i.immediate & 0x0000ffff)),
        CreateAddu(i.rt, i.rs, 1),
        };
        
        for(int j = 0; j < 3; j++){
        addLast(tals, addiuSet[j]);
        }
    }
    else if (i.instruction_id == blt){
        struct Instruction bltSet[2] = {
            CreateSlt(1, i.rt, i.rs),
            CreateBne(1, 0, i.branch_label),
        };
        
        for(int j = 0; j < 2; j++){
        addLast(tals, bltSet[j]);
        }
    }
    else if (i.instruction_id == bge){
        struct Instruction bgeSet[2] = {
            CreateSlt(1, i.rt, i.rs),
            CreateBeq(1, 0, i.branch_label),
        };
        
        for(int j = 0; j < 2; j++){
        addLast(tals, bgeSet[j]);
        }
    }
    else if (i.instruction_id == ori && (i.immediate > 0x00007fff || i.immediate < 0xffff8001)){
        struct Instruction oriSet[3] = {
        CreateLui(1, (i.immediate >> 16) & 0xffffffff),
        CreateOri(1, 1, (i.immediate & 0x0000ffff)),
        CreateOr(i.rt, i.rs, 1),
        };
        
        for(int j = 0; j < 3; j++){
        addLast(tals, oriSet[j]);
        }
    }
    else if (i.instruction_id == mov){
        addLast(tals, CreateAddu(i.rd, 0, i.rt));
    }
    else{
        addLast(tals, i);
    }
    }
}
