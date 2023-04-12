## Positive jumps
ADDI $t0, $zero, 0          #0
ADDI $s7, $zero, 20         #1


##      JR      ##
JR $s7                      #2
ADDI $t0, $t0, 1        #OK #3
ADDI $t0, $t0, 2        #ko #4
ADDI $t0, $t0, 4        #OK #5

##      J       ##
J 9                         #6
ADDI $t0, $t0, 8        #OK #7
ADDI $t0, $t0, 16       #ko #8
ADDI $t0, $t0, 32       #OK #9

##     JAL      ##
JAL 13                      #10
ADDI $t0, $t0, 64       #OK #11
ADDI $t0, $t0, 128      #ko #12
ADDI $t0, $t0, 256      #OK #13


## 0 jumps
ADDI $s6, $zero, 68         #14
ADDI $t1, $zero, 0          #15

##      JR      ##
JR $s6                      #16
ADDI $t1, $t1, 1        #2x #17
ADDI $t1, $t1, 4        #OK #18

##      J       ##
J 20                        #19
ADDI $t1, $t1, 8        #2x #20
ADDI $t1, $t1, 32       #OK #21

##     JAL      ##
JAL 23                      #22
ADDI $t1, $t1, 64       #2x #23
ADDI $t1, $t1, 256      #OK #24


## Negative jumps
ADDI $s5, $zero, 108        #25
ADDI $t2, $zero, 0          #26

##      JR      ##
ADDI $t3, $t2, -0           #27
BGTZ $t3, 4                 #28
NOP                         #29
JR $s5                      #30
ADDI $t2, $t2, 1        #OK #31
ADDI $t2, $t2, 4        #ko #32


##      J       ##
ADDI $t3, $t2, -8           #33
BGTZ $t3, 4                 #34
NOP                         #35
J 33                        #36
ADDI $t2, $t2, 8        #OK #37
ADDI $t2, $t2, 32       #ko #38


##     JAL      ##
ADDI $t3, $t2, -72          #39
BGTZ $t3, 4                 #40
NOP                         #41
JAL 39                      #42
ADDI $t2, $t2, 64       #OK #43
ADDI $t2, $t2, 256      #ko #44

NOP


# EXPECTED_ASSEMBLY 
# 20080000
# 20170014
# 02E00008
# 21080001
# 21080002
# 21080004
# 08000009
# 21080008
# 21080010
# 21080020
# 0C00000D
# 21080040
# 21080080
# 21080100
# 20160044
# 20090000
# 02C00008
# 21290001
# 21290004
# 08000014
# 21290008
# 21290020
# 0C000017
# 21290040
# 21290100
# 2015006C
# 200A0000
# 214B0000
# 1D600004
# 00000000
# 02A00008
# 214A0001
# 214A0004
# 214BFFF8
# 1D600004
# 00000000
# 08000021
# 214A0008
# 214A0020
# 214BFFB8
# 1D600004
# 00000000
# 0C000027
# 214A0040
# 214A0100
# 00000000


# EXPECTED_FINAL_STATE
# $08:365	
# $09:438	
# $10:73  	
# $11:1  	
# $21:108  	
# $22:68 	
# $23:20	
# $31:176	
