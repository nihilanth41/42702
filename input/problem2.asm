% load integers into memory
% addr 0x10010000000000
addiu $a3,$zero,0x1001
sll $a0,$a3,10
addiu $t0,$zero,5
sw $t0,0($a0)
addiu $t0,$zero,3
sw $t0,4($a0)
addiu $t0,$zero,6
sw $t0,8($a0)
addiu $t0,$zero,8
sw $t0,12($a0)
addiu $t0,$zero,9
sw $t0,16($a0)
addiu $t0,$zero,1
sw $t0,20($a0)
addiu $t0,$zero,4
sw $t0,24($a0)
addiu $t0,$zero,7
sw $t0,28($a0)
addiu $t0,$zero,2
sw $t0,32($a0)
addiu $t0,$zero,a
sw $t0,36($a0)
syscall
