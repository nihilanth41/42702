#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define BUF_SIZE 128

#define NUM_OPS 3
#define NUM_REGS 8
char *OP_STRINGS[] = { "addiu", "bne", "syscall" };
uint32_t OPCODES[] = { 0x24000000, 0x14000000, 0x0 };

char *REG_STRINGS[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3" };
uint32_t REGCODES[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			           // 0   1     2    3 


int main(int argc, char **argv) {
//[0x04000000] addiu $a0, $zero, 0 
//[0x04000014] bne $a1, $a2, -8 
// if branch taken, then jump to head of loop at 0x400000c
	if(argc < 2) { 
		printf("Usage is: %s <input.asm>\n", argv[0]);
		return -1;
	}	

	char buf[BUF_SIZE] = { 0 };

	char *filepath = argv[1];
	FILE *fp_r = fopen(filepath, "r"); 
	if(NULL == fp_r) { 
		exit(-1); 
	}
	
	// For each line of input assembly
	while( fgets(buf, BUF_SIZE, fp_r) != NULL ) {
		char *op, *rs, *rt, *immediate;
		// Token on space between instruction and operands
//        if (strcmp(buf, OP_STRINGS[2]) == 0 ){
//            op = 0x0;
//            printf("%s", op);
//        }
//        else{
		op = strtok(buf, " ");
        if (strcmp(op, OP_STRINGS[0]) == 0){
            rt = strtok(NULL, ",");
            rs = strtok(NULL, ",");
        }
        if (strcmp(op, OP_STRINGS[1]) == 0){
            rs = strtok(NULL, ",");
            rt = strtok(NULL, ",");
        }
//		rt = strtok(NULL, ",");
//		rs = strtok(NULL, ",");
		immediate = strtok(NULL, "\n");
        if (strcmp(op, OP_STRINGS[2]) == 0){
            printf("syscall 0000000c\n");
            break;
        }
        else
		  printf("%s %s,%s,%s\n", op, rs, rt, immediate);
		
		uint32_t opc, op1, op2;

		int i;
		for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("%x\n", opc);
				break;	
			}
		}
		for(i=0; i<NUM_REGS; i++) { 
			if(0 == strcmp(rs, REG_STRINGS[i])) {
				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
				printf("%x\n", op1);
				break;
			}
		}
		for(i=0; i<NUM_REGS; i++) { 
			if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				printf("%x\n", op2);
				break;
			}
		}
		// replace trailing \n with nul terminator
		//immediate[strlen(immediate)-1] = '\0';
		uint16_t immediate_int = (uint16_t)strtol(immediate, NULL, 16);
		
		printf("Immediate: %d\n", immediate_int);
        if (0 == strcmp(OP_STRINGS[1], op)){
        uint32_t machine_code = opc+op1+op2+((immediate_int >> 2) | 0xf000);
		printf("machine code: %x\n", machine_code);
        }
        else{
		uint32_t machine_code = opc+op1+op2+immediate_int;
		printf("machine code: %x\n", machine_code);
        }
//        }
    }

	return EXIT_SUCCESS;
	
}
