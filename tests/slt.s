## Constantes
ADDI $s0, $zero, -2
ADDI $s1, $zero, -1
ADDI $s2, $zero, -1
ADDI $s3, $zero, 0
ADDI $s4, $zero, 1
ADDI $s5, $zero, 1
ADDI $s6, $zero, 2


##     SLT      ##
ADDI $t0, $zero, 0
ADDI $t1, $zero, 0

SLT $t0, $s1, $s2  # -1 -1  #ko
SLL $t0, $t0, 0
OR $t1, $t1, $t0 

SLT $t0, $s4, $s5  #  1  1  #ko
SLL $t0, $t0, 1
OR $t1, $t1, $t0 

SLT $t0, $s4, $s6  #  1  2  #OK
SLL $t0, $t0, 2
OR $t1, $t1, $t0 

SLT $t0, $s0, $s1  # -2 -1     #OK
SLL $t0, $t0, 3
OR $t1, $t1, $t0 

SLT $t0, $s6, $s1  #  2 -1     #ko
SLL $t0, $t0, 4
OR $t1, $t1, $t0 

SLT $t0, $s6, $s4  #  2  1     #ko
SLL $t0, $t0, 5
OR $t1, $t1, $t0 

SLT $t0, $s1, $s0  # -1 -2     #ko
SLL $t0, $t0, 6
OR $t1, $t1, $t0 

SLT $t0, $s6, $s1  #  2 -1     #ko
SLL $t0, $t0, 7
OR $t1, $t1, $t0 


# EXPECTED_ASSEMBLY 
# 2010FFFE
# 2011FFFF
# 2012FFFF
# 20130000
# 20140001
# 20150001
# 20160002
# 20080000
# 20090000
# 0232402A
# 00084000
# 01284825
# 0295402A
# 00084040
# 01284825
# 0296402A
# 00084080
# 01284825
# 0211402A
# 000840C0
# 01284825
# 02D1402A
# 00084100
# 01284825
# 02D4402A
# 00084140
# 01284825
# 0230402A
# 00084180
# 01284825
# 02D1402A
# 000841C0
# 01284825


# EXPECTED_FINAL_STATE
# $08:0
# $09:12
# $16:-2
# $17:-1
# $18:-1
# $19:0
# $20:1
# $21:1
# $22:2