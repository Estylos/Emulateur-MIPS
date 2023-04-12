ADDI $t0, $zero, 120 # 0x78
ADDI $t1, $zero, 599 # 0x257

AND $t2, $t0, $t1 # 120 AND 599 = 80 (0x50)
OR $t3, $t0, $t1 # 120 OR 599 = 639 (0x27F)
XOR $t4, $t0, $t1 # 120 XOR 599 = 559 (0x22F)

SLL $t5, $t2, 5 # 80 << 5 = 2560 (0xA00)
SRL $t6, $t3, 3 # 639 >> 3 = 79 (0x4F)
ROTR $t7, $t0, 7 # 120 rotation droite de 7 = -268435456 (signé) (0xF0000000) 
SYSCALL # Test du syscall
NOP
NOP

# EXPECTED_ASSEMBLY
# 20080078
# 20090257
# 01095024
# 01095825
# 01096026
# 000A6940
# 000B70C2
# 002879C2
# 0000000C
# 00000000
# 00000000

# EXPECTED_FINAL_STATE
# $08:120
# $09:599
# $10:80
# $11:639
# $12:559
# $13:2560
# $14:79
# $15:-268435456