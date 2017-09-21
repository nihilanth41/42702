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


int main(int argc, char **argv) {
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
		char *op=NULL, *rs=NULL, *rt=NULL, *immediate=NULL;
		
		// Ignore comments if found
		if('%' == buf[0]) {
			//printf("%s", buf);
			continue;
		}

		op = strtok(buf, " ");

		if (strcmp(op, OP_STRINGS[0]) == 0){
			rt = strtok(NULL, ",");
			rs = strtok(NULL, ",");
		} 
		else if (strcmp(op, OP_STRINGS[1]) == 0){
			rs = strtok(NULL, ",");
			rt = strtok(NULL, ",");
		} 
		else if (strncmp(op, OP_STRINGS[2], strlen(OP_STRINGS[2])) == 0){
			printf("syscall 0000000c\n");
			break;
		}
		else {
			// Print syntax errors if found
			printf("Syntax error: %s", buf); 
			//printf("Token: %s\n", op);
			exit(-2);
		}
		immediate = strtok(NULL, "\n");

		//printf("%s %s,%s,%s\t", op, rs, rt, immediate);
		
		uint32_t opc=0, op1=0, op2=0;
		int i=0;

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
				//printf("%x\n", op1);
				break;
			}
		}
		for(i=0; i<NUM_REGS; i++) { 
			if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("%x\n", op2);
				break;
			}
		}
		uint16_t immediate_int = (uint16_t)strtol(immediate, NULL, 16);
		uint32_t machine_code = 0;
		
		//printf("Immediate: %d\n", immediate_int);
		if (0 == strcmp(OP_STRINGS[1], op)){
			machine_code = opc+op1+op2+((immediate_int >> 2) | 0xf000);
		}
		else{
			machine_code = opc+op1+op2+immediate_int;
		}
		printf("%x\n", machine_code);
	}

	return EXIT_SUCCESS;
}
