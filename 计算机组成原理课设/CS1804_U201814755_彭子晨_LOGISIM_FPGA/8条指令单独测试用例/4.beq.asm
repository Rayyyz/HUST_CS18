#############################################################
#����beqָ���һ��bneӦ�ò������ڶ���Ӧ����ת
#############################################################
.text
addi $1,$0,1

beq $1, $0, Next1   # should not branch
beq $1, $1, Next1   # shoud branch
nop
nop
nop
Next1:
 addi   $v0,$0,10         # system call for display
 syscall                 # syscall include 2 hidden operand: $v0,$a0��may cause data hazzard
