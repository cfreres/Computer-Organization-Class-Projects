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

void resolve_addresses(struct ArrayList *unresolved, uint32_t first_pc, struct ArrayList *resolved) {
    
    typedef struct labelAddress{
        char* label;
        int32_t address;
        struct labelAddress *next;
    }labelAddress;
    
    labelAddress *head = NULL;
    
    //struct labelAddress *current = NULL;
    
    void add(char* lab, int32_t addr){
        labelAddress *temp = malloc(sizeof(labelAddress));
        
        temp -> label = malloc(400 * sizeof(char));
        strcpy(temp -> label, lab);
        temp -> address = addr;
        temp -> next = head;
        
        head = temp;
    }
    
    labelAddress* findAddress(char* lab, labelAddress *temp){
        if (temp == NULL) return NULL;
        
        if (strcmp(lab, temp -> label) != 0){
            return findAddress(lab, temp -> next);
        }
        else {
            return temp;
        }     
    }
    void freeAddresses(labelAddress *temp){
        if (temp -> next != NULL){
        freeAddresses(temp -> next);
        if(temp -> label != NULL) free(temp -> label);
        free(temp);
        }
    }
    
    struct Instruction instruction;
    
    for (int i = 0; i < size(unresolved); i++){
        instruction = get(unresolved, i);
        if ((strcmp(instruction.label, "") != 0)){
            add(instruction.label, (first_pc + (4*i)));
        }          
    }
    
    labelAddress *tempAddress;
    for (int i = 0; i < size(unresolved); i++){
        instruction = get(unresolved, i);
        if ((strcmp(instruction.branch_label, "") != 0)){
            int32_t curLocation = first_pc + (4*i);
            tempAddress = findAddress(instruction.branch_label, head);
            if (tempAddress != NULL){
                memset(instruction.branch_label, 0, sizeof(instruction.branch_label));
                int imm =  (((tempAddress -> address) - curLocation) / 4) - 1;
                instruction.immediate = imm;
            }
        }
        addLast(resolved, instruction);
    }
    
    freeAddresses(head);
}

