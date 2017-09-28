% load integers into memory
% addr 0x1001000
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

% $a1 - addr for storing sorted list
% overwrite old $a3 value we dont need it anymore (addr of unsorted list is in $a0)
addiu $a3,$zero,0x1002
sll $a1,$a3,10

% iterate through - same as example from lab document
% $t1 is upper bound for iterator, $t2 is iterator i

% initial values
addiu $t1,$zero,0xA
addiu $t2,$zero,0

%find smallest element in unsorted list 
% $t3 contains the minimum-element so-far (while we iterate) - initialize to 0
addiu $t3,$zero,0


% increment i
addiu $t2,$t2,0x01

% Change -8 to the beginning of the finding the smallest element.
bne $t1,$t2,-8 





syscall
