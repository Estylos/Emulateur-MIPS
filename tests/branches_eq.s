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
ADDI $t2, $zero, 0

##     BEQ      ##
BEQ $s1, $s2, 2   # -1 -1
ADDI $t2, $t2, 1            #OK
ADDI $t0, $t0, 1            #ko
ADDI $t0, $t0, 2            #OK

BEQ $s4, $s5, 2   #  1  1
ADDI $t2, $t2, 2            #OK
ADDI $t0, $t0, 4            #ko
ADDI $t0, $t0, 8            #OK

BEQ $s1, $s0, 2   # -1 -2
ADDI $t2, $t2, 4            #OK
ADDI $t0, $t0, 16           #OK
ADDI $t0, $t0, 32           #OK

BEQ $s5, $s6, 2   #  1  2
ADDI $t2, $t2, 8            #OK
ADDI $t0, $t0, 64           #OK
ADDI $t0, $t0, 128          #OK

BEQ $s1, $s4, 2   #  -1  1
ADDI $t2, $t2, 16           #OK
ADDI $t0, $t0, 256          #OK
ADDI $t0, $t0, 512          #OK

##     BNE      ##
BNE $s1, $s2, 2  # -1 -1
ADDI $t2, $t2, 32           #OK
ADDI $t1, $t1, 1            #OK
ADDI $t1, $t1, 2            #OK

BNE $s4, $s5, 2   #  1  1
ADDI $t2, $t2, 64           #OK
ADDI $t1, $t1, 4            #OK
ADDI $t1, $t1, 8            #OK

BNE $s1, $s0, 2   # -1 -2
ADDI $t2, $t2, 128          #OK
ADDI $t1, $t1, 16           #ko
ADDI $t1, $t1, 32           #OK

BNE $s4, $s6, 2   #  1  2
ADDI $t2, $t2, 256          #OK
ADDI $t1, $t1, 64           #ko
ADDI $t1, $t1, 128          #OK

BNE $s1, $s4, 2   #  -1  1
ADDI $t2, $t2, 512          #OK
ADDI $t1, $t1, 256          #ko
ADDI $t1, $t1, 512          #OK


## 0 branches
ADDI $t3, $zero, 0

##     BEQ      ##
BEQ $s1, $s2, 0   # -1 -1
ADDI $t3, $t3, 1            #2x
ADDI $t3, $t3, 4            #OK

#      BNE      ##
BNE $s1, $s0, 0   # -1 -2
ADDI $t3, $t3, 8            #2x
ADDI $t3, $t3, 32           #OK


## Negative branches    
ADDI $t4, $zero, 0

##     BEQ      ##
ADDI $t5, $t4, -0          
BGTZ $t5, 4                
NOP                   
BEQ $s1, $s2, -4   # -1 -1
ADDI $t4, $t4, 1            #OK
ADDI $t4, $t4, 4            #ko

#      BNE      ##
ADDI $t5, $t4, -1         
BGTZ $t5, 4                
NOP    
BNE $s1, $s0, -4   # -1 -2
ADDI $t4, $t4, 8            #OK
ADDI $t4, $t4, 32           #ko

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
# 200A0000
# 12320002
# 214A0001
# 21080001
# 21080002
# 12950002
# 214A0002
# 21080004
# 21080008
# 12300002
# 214A0004
# 21080010
# 21080020
# 12B60002
# 214A0008
# 21080040
# 21080080
# 12340002
# 214A0010
# 21080100
# 21080200
# 16320002
# 214A0020
# 21290001
# 21290002
# 16950002
# 214A0040
# 21290004
# 21290008
# 16300002
# 214A0080
# 21290010
# 21290020
# 16960002
# 214A0100
# 21290040
# 21290080
# 16340002
# 214A0200
# 21290100
# 21290200
# 200B0000
# 12320000
# 216B0001
# 216B0004
# 16300000
# 216B0008
# 216B0020
# 200C0000
# 218D0000
# 1DA00004
# 00000000
# 1232FFFC
# 218C0001
# 218C0004
# 218DFFFF
# 1DA00004
# 00000000
# 1630FFFC
# 218C0008
# 218C0020
# 00000000


# EXPECTED_FINAL_STATE
# $08:1018	
# $09:687	
# $10:1023  	
# $11:54
# $12:9
# $13:8
# $16:-2
# $17:-1
# $18:-1
# $19:0
# $20:1
# $21:1
# $22:2
