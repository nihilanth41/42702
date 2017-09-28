//r1 = $t0 = 2 numbers ago
//r2 = $t1 = 1 number ago
//r3 = $t2 = current number (where the end result will be stored)
//r4 = $t3 = counter
//r5 = $t4 = USER INPUT number within sequence

addiu $t4, $zero, A				//initialize counter to 10				
addiu $t3, $zero, 0				//counter 0
addiu $t0, $zero, 0				//L2 = 0
addiu $t1, $zero, 1				//L1 = 1
addiu $t2, $zero, 0				//current = 0
beq $t3, $t4, 18				//if counter == user input, go to end of program
addiu $t0, $t1, 0				//LABEL 1					
addiu $t1, $t2, 0
add $t2, $t0, $t1				//else, add L2 and L1 and put it in r3
addiu $t3, $t3, 1				//counter increments
bne $t3, $t4, -10				//send to LABEL 1 if count != user input
syscall						//End program

