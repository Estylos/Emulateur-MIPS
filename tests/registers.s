# Tests d'appel de tous les registres 

add $0, $at, $1
add $0, $v0, $2
add $0, $v1, $3
add $0, $a0, $4
add $0, $a1, $5
add $0, $a2, $6
add $0, $a3, $7
add $0, $t0, $8
add $0, $t1, $9
add $0, $t2, $10
add $0, $t3, $11
add $0, $t4, $12
add $0, $t5, $13
add $0, $t6, $14
add $0, $t7, $15
add $0, $s0, $16
add $0, $s1, $17
add $0, $s2, $18
add $0, $s3, $19
add $0, $s4, $20
add $0, $s5, $21
add $0, $s6, $22
add $0, $s7, $23
add $0, $t8, $24
add $0, $t9, $25
add $0, $k0, $26
add $0, $k1, $27
add $0, $gp, $28
add $0, $sp, $29
add $0, $fp, $30
add $0, $ra, $31

# EXPECTED_ASSEMBLY 
# 00210020
# 00420020
# 00630020
# 00840020
# 00A50020
# 00C60020
# 00E70020
# 01080020
# 01290020
# 014A0020
# 016B0020
# 018C0020
# 01AD0020
# 01CE0020
# 01EF0020
# 02100020
# 02310020
# 02520020
# 02730020
# 02940020
# 02B50020
# 02D60020
# 02F70020
# 03180020
# 03390020
# 035A0020
# 037B0020
# 039C0020
# 03BD0020
# 03DE0020
# 03FF0020

# EXPECTED_FINAL_STATE
# $00:0