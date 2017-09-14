#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

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
		char *tok = NULL;
		// Token on space between instruction and operands
		tok = strtok(buf, " ");
		while(tok != NULL) {
			printf("token: %s\n", tok);
			tok = strtok(NULL, ",");

		}
		printf("\n");
		
	}

	return EXIT_SUCCESS;
	
}
