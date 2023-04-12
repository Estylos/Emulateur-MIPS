## Constantes
ADDI $s0, $zero, -2
ADDI $s1, $zero, -1
ADDI $s2, $zero, -1
ADDI $s3, $zero, 0
ADDI $s4, $zero, 1
ADDI $s5, $zero, 1
ADDI $s6, $zero, 2


## Positive branches
ADDI $t0, $zero, 0
ADDI $t1, $zero, 0

##     BGTZ     ##
BGTZ $s1, 2      # -1
ADDI $t1, $t1, 1            #OK
ADDI $t0, $t0, 1            #OK
ADDI $t0, $t0, 2            #OK

BGTZ $s3, 2      #  0
ADDI $t1, $t1, 2            #OK
ADDI $t0, $t0, 4            #OK
ADDI $t0, $t0, 8            #OK

BGTZ $s4, 2      #  1
ADDI $t1, $t1, 4            #OK
ADDI $t0, $t0, 16           #ko
ADDI $t0, $t0, 32           #OK

##     BLEZ     ##
BLEZ $s1, 2      # -1
ADDI $t1, $t1, 8            #OK
ADDI $t0, $t0, 64           #ko
ADDI $t0, $t0, 128          #OK

BLEZ $s3, 2      #  0
ADDI $t1, $t1, 16           #OK
ADDI $t0, $t0, 256          #ko
ADDI $t0, $t0, 512          #OK

BLEZ $s4, 2      #  1
ADDI $t1, $t1, 32           #OK
ADDI $t0, $t0, 1024         #OK
ADDI $t0, $t0, 2048         #OK


## 0 branches
ADDI $t2, $zero, 0

##     BGTZ     ##
BGTZ $s4, 0      #  1
ADDI $t2, $t2, 1           #2x
ADDI $t2, $t2, 4           #OK

##     BLEZ     ##
BLEZ $s1, 0      # -1
ADDI $t2, $t2, 8           #2x
ADDI $t2, $t2, 32          #OK


## Negative branches
ADDI $t3, $zero, 0

##     BGTZ     ##
ADDI $t4, $t3, -0          
BGTZ $t4, 4                
NOP                   
BGTZ $s4, -4      #  1
ADDI $t3, $t3, 1            #OK
ADDI $t3, $t3, 2            #ko

##     BLEZ     ##
ADDI $t4, $t3, -1         
BGTZ $t4, 4                
NOP       
BLEZ $s1, -4     # -1
ADDI $t3, $t3, 4            #OK
ADDI $t3, $t3, 8            #ko

NOP


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
# 1E200002
# 21290001
# 21080001
# 21080002
# 1E600002
# 21290002
# 21080004
# 21080008
# 1E800002
# 21290004
# 21080010
# 21080020
# 1A200002
# 21290008
# 21080040
# 21080080
# 1A600002
# 21290010
# 21080100
# 21080200
# 1A800002
# 21290020
# 21080400
# 21080800
# 200A0000
# 1E800000
# 214A0001
# 214A0004
# 1A200000
# 214A0008
# 214A0020
# 200B0000
# 216C0000
# 1D800004
# 00000000
# 1E80FFFC
# 216B0001
# 216B0002
# 216CFFFF
# 1D800004
# 00000000
# 1A20FFFC
# 216B0004
# 216B0008
# 00000000


# EXPECTED_FINAL_STATE
# $08:3759
# $09:63
# $10:54 	
# $11:5
# $12:4
# $16:-2
# $17:-1
# $18:-1
# $19:0
# $20:1
# $21:1
# $22:2