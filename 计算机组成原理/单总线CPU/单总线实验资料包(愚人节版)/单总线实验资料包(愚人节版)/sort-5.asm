 .text
#################################################################################
#������ʵ�֣��ֽڵ�ַ0x200���ֵ�ַ0x80����ʼ��8���ֵ�Ԫ�Ľ�������,�˳������mars mips������������,����ʱ�뽫Mars Setting�е�Memory Configuration����ΪCompact��data at address 0
##################################################################################
 .text
sort_init:
 addi $s0,$0,-1
 addi $s1,$0,0
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,512($s1)
 
 add $s0,$zero,0   
 addi $s1,$zero,28   #��������
sort_loop:
 lw $s3,512($s0)     
 lw $s4,512($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #��������
 sw $s3, 512($s1)
 sw $s4, 512($s0)   
sort_next:
 addi $s1, $s1, -4   
 beq $s0, $s1,  sort_next1  
 beq $0,$0,sort_loop
sort_next1:
 addi $s0,$s0,4
 addi $s1,$zero,28
 beq $s0, $s1, ProgramEnd
 beq $0,$0,sort_loop
 ProgramEnd:beq $0,$0,ProgramEnd  #��ѭ��
