#show
.text	 
addi $s1,$0,100000  #s1��¼ѭ������
addi $s2,$0,0    #s2��¼��ǰͼƬλ��
bne_branch:
lw $a0,0($s2)          #��ȡͼƬ����
addi $v0,$0,34         
syscall              #�����ǰֵ
addi $s2,$s2,4	      #��һ��ͼƬ
addi $s1,$s1,-1		
bne $s1,$0,bne_branch   #����ָ��

addi   $v0,$zero,10      #ͣ��ָ��
syscall                  #ϵͳ����
