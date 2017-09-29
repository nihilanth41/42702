#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define BUF_SIZE 128

#define NUM_OPS 10
#define NUM_REGS 19
char *OP_STRINGS[] = { "addiu", "bne", "sw", "beq", "add", "sub", "sll", "lw", "slt", "syscall" };
uint32_t OPCODES[] = { 0x24000000, 0x14000000, 0xac000000, 0x10000000, 0x00000020, 0x00000022, 0x0, 0x8c000000, 0x0000002a, 0x0000000c };

char *REG_STRINGS[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2" };
uint32_t REGCODES[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 }; //10000, 10001, 10010


int main(int argc, char **argv) {
//printf("%s\n", REG_STRINGS[18]);
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
		char *op, *rs, *rt, *immediate, *offset, *rd, *sa, *base;
        uint32_t opc, op1, op2, op3, op4;
		int i;
        uint16_t immediate_int, offset_int, sa_int;
		op = strtok(buf, " ");
        if (strcmp(op, OP_STRINGS[9]) == 0){
            printf("0000000c\n");
            break;
        }
        if (strcmp(op, OP_STRINGS[0]) == 0){
            rt = strtok(NULL, ",");
            rs = strtok(NULL, ",");
            immediate = strtok(NULL, "\n");
            immediate_int = (uint16_t)strtol(immediate, NULL, 16);
        for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("opc:%x\n", opc);
				//break;	
			}
	}
	for(i=0; i<NUM_REGS; i++) {
            if(0 == strcmp(rs, REG_STRINGS[i])) {
				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
				//printf("op1:%x\n", op1);
				//break;
			}
            if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("op2:%x\n", op2);
				//break;
			}
		}
        uint32_t machine_code = opc+op1+op2+immediate_int;
		printf("%x\n", machine_code);
        }
        if (strcmp(op, OP_STRINGS[1]) == 0 || strcmp(op, OP_STRINGS[3]) == 0){
            rs = strtok(NULL, ",");
            rt = strtok(NULL, ",");
            immediate = strtok(NULL, "\n");
            immediate_int = (uint16_t)strtol(immediate, NULL, 16);
        for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("%x\n", opc);
				//break;	
			}
	}
	for(i=0; i<NUM_REGS; i++) {
            if(0 == strcmp(rs, REG_STRINGS[i])) {
				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
				//printf("%x\n", op1);
				//break;
			}
            if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("%x\n", op2);
				//break;
			}
		}
        if ((0 == strcmp(OP_STRINGS[1], op) && immediate_int >> 15 == 1) || (0 == strcmp(OP_STRINGS[3], op) && immediate_int >> 15 == 1)){
        uint32_t machine_code = opc+op1+op2+((immediate_int >> 2) | 0xc000);
		printf("%x\n", machine_code);
        }
        if ((0 == strcmp(OP_STRINGS[1], op) && immediate_int >> 15 == 0) || (0 == strcmp(OP_STRINGS[3], op) && immediate_int >> 15 == 0)){
		uint32_t machine_code = opc+op1+op2+(immediate_int >> 2 | 0);
		printf("%x\n", machine_code);
        }    
        }
        if (strcmp(op, OP_STRINGS[2]) == 0 || strcmp(op, OP_STRINGS[7]) == 0){
            rt = strtok(NULL, ",");
            //printf("rt=%s\n", rt);
            offset = strtok(NULL, "(");
            base = strtok(NULL, ")");
            offset_int = (uint16_t)strtol(offset, NULL, 10);
        for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("opc:%x\n", opc);
				//break;	
			}
	}
	for(i=0; i<NUM_REGS; i++) {
            if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("op2:%x\n", op2);
				//break;
			}
            if(0 == strcmp(base, REG_STRINGS[i])) {
				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
				//printf("op1:%x\n", op1);
				//break;
			}
		}
            //printf("%s %s,%s(%s)\n", op, rt, offset, base);
        uint32_t machine_code = opc+op1+op2+offset_int;
		printf("%x\n", machine_code);
        }
        if (strcmp(op, OP_STRINGS[4]) == 0 || strcmp(op, OP_STRINGS[5]) == 0 || strcmp(op, OP_STRINGS[8]) == 0){
            rd = strtok(NULL, ",");
            rs = strtok(NULL, ",");
            rt = strtok(NULL, "\n");
        for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("%x\n", opc);
				//break;	
			}
	}
	for(i=0; i<NUM_REGS; i++) {
            if(0 == strcmp(rs, REG_STRINGS[i])) {
				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
				//printf("%x\n", op1);
				//break;
			}
            if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("%x\n", op2);
				//break;
			}
            if(0 == strcmp(rd, REG_STRINGS[i])) {
				op3 = ((REGCODES[i] ) << 11) & 0xfffff800;
				//printf("%x\n", op3);
				//break;
			}
		}
        uint32_t machine_code = opc+op1+op2+op3;
		printf("%x\n", machine_code);
        }
        if (strcmp(op, OP_STRINGS[6]) == 0){
            rd = strtok(NULL, ",");
            rt = strtok(NULL, ",");
            //printf("rt: %s\n", rt);
            sa = strtok(NULL, "\n");
        for(i=0; i<NUM_OPS; i++) {
			if(0 == strcmp(OP_STRINGS[i], op)) {
				opc = OPCODES[i];
				//printf("opc:%x\n", opc);
				//break;	
			}
		}
	for(i=0; i<NUM_REGS; i++) {
            if(0 == strcmp(rt, REG_STRINGS[i])) {
				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
				//printf("op2:%x\n", op2);
				//break;
			}
            if(0 == strcmp(rd, REG_STRINGS[i])) {
				op3 = ((REGCODES[i] ) << 11) & 0xfffff800;
				//printf("op3:%x\n", op3);
				//break;
			}
                sa_int = (uint16_t)strtol(sa, NULL, 16) << 6;
		}
        uint32_t machine_code = opc+op2+op3+sa_int;
		printf("%x\n", machine_code);
        }
		  //printf("%s %s,%s,%s\n", op, rs, rt, immediate);

//		for(i=0; i<NUM_OPS; i++) {
//			if(0 == strcmp(OP_STRINGS[i], op)) {
//				opc = OPCODES[i];
//				printf("%x\n", opc);
//				break;	
//			}
//		}
//		for(i=0; i<NUM_REGS; i++) { 
//			if(0 == strcmp(rs, REG_STRINGS[i])) {
//				op1 = ((REGCODES[i] ) << 21) & 0xffe00000;
//				printf("%x\n", op1);
//				break;
//			}
//		}
//		for(i=0; i<NUM_REGS; i++) { 
//			if(0 == strcmp(rt, REG_STRINGS[i])) {
//				op2 = ((REGCODES[i] ) << 16) & 0xffff0000;
//				printf("%x\n", op2);
//				break;
//			}
//		}
//        for(i=0; i<NUM_REGS; i++) { 
//			if(0 == strcmp(rd, REG_STRINGS[i])) {
//				op3 = ((REGCODES[i] ) << 11) & 0xfffff800;
//				printf("%x\n", op3);
//				break;
//			}
//		}
//		for(i=0; i<NUM_REGS; i++) { 
//			if(0 == strcmp(sa, REG_STRINGS[i])) {
//				op4 = ((REGCODES[i] ) << 6) & 0xffffffc0;
//				printf("%x\n", op4);
//				break;
//			}
//		}
//		
//		//printf("Immediate: %d\n", immediate_int);
//        if (0 == strcmp(OP_STRINGS[0], op)){
//		uint32_t machine_code = opc+op1+op2+immediate_int;
//		printf("%x\n", machine_code);
//        }
//        if ((0 == strcmp(OP_STRINGS[1], op) && immediate_int >> 15 == 1) || (0 == strcmp(OP_STRINGS[3], op) && immediate_int >> 15 == 1)){
//        uint32_t machine_code = opc+op1+op2+((immediate_int >> 2) | 0xf000);
//		printf("%x\n", machine_code);
//        }
//        if ((0 == strcmp(OP_STRINGS[1], op) && immediate_int >> 15 == 0) || (0 == strcmp(OP_STRINGS[3], op) && immediate_int >> 15 == 0)){
//		uint32_t machine_code = opc+op1+op2+(immediate_int >> 2);
//		printf("%x\n", machine_code);
//        }
//        if (0 == strcmp(OP_STRINGS[2], op) || 0 == strcmp(OP_STRINGS[7], op)){
//		uint32_t machine_code = opc+op1+op2+offset_int;
//		printf("%x\n", machine_code);
//        }
//        if (0 == strcmp(OP_STRINGS[4], op) || 0 == strcmp(OP_STRINGS[5], op) || 0 == strcmp(OP_STRINGS[8], op)){
//		uint32_t machine_code = opc+op1+op2+op3;
//		printf("%x\n", machine_code);
//        }
//        if (0 == strcmp(OP_STRINGS[6], op)){
//		uint32_t machine_code = opc+op2+op3+op4;
//		printf("%x\n", machine_code);
//        }
        
    }

	return EXIT_SUCCESS;
	
}
