#show
.text	 
addi $s1,$0,100000  #s1记录循环次数
addi $s2,$0,0    #s2记录当前图片位置
bne_branch:
lw $a0,0($s2)          #获取图片数据
addi $v0,$0,34         
syscall              #输出当前值
addi $s2,$s2,4	      #下一张图片
addi $s1,$s1,-1		
bne $s1,$0,bne_branch   #测试指令

addi   $v0,$zero,10      #停机指令
syscall                  #系统调用
