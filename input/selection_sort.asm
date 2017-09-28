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

addiu $t0,$zero,0xA 	// n = 10
addiu $t1,$zero,0x09 	// n-1 = 9
addiu $t3,$zero,0	// j = 0
sll $t6,$t3,2		// $t6 = j*4
add $t7,$a0,$t6		// $t7 = &a[j]
add $t8,$zero,$t3	// iMin = j
addiu $t2,$t3,1		// i = j+1		
sll $t9,$t8,2		// $t9 = iMin*4		// TOP_INNER:	
add $s0,$a0,$t9		// $s0 = &a[iMin]
sll $t4,$t2,2		// $t4 = i*4
add $t5,$a0,$t4		// $t5 = &a[i]
lw $s2,0($t5)		// $s2 = a[i]
lw $s3,0($s0)		// $s3 = a[iMin]
slt $s1,$s2,$s3		// $s1 = (a[i] < a[iMin]) ? 1 : 0
beq $s1,$zero,8		// skip next if $s1==0 
add $t8,$zero,$t2	// (true) => iMin = i
slt $s1,$t2,$t0		// $s1 = (i<n) ? 1 : 0 
blez 12			// skip next two if false
addiu $t2,$zero,1	// i = i+1
j -48			// jump to TOP_INNER 	
			// else check iMin != j
			// swap if true
			// check if j<n-1	
			// increment j












