ADDI $t0, $zero, 2000 # 1er valeur arbitraire
LUI $t1, 1911 # 2e valeur arbitraire (1911 << 16 = 125239296)

ADDI $sp, $sp, -4 # Sommet pile -4
SW $t0, 0($sp) # On place $t0 au sommet de la pile
SW $t1, 4($sp) # On place $t1 au sommet de la pile + 4 octets

LW $t0, 4($sp) # On récupère 125239296 ($t1) dans $t0
LW $t1, 0($sp) # On récupère 2000 ($t0) dans $t1

ADDI $sp, $sp, 4 # On revient au sommet de la pile

# EXPECTED_ASSEMBLY
# 200807D0
# 3C090777
# 23BDFFFC
# AFA80000
# AFA90004
# 8FA80004
# 8FA90000
# 23BD0004

# EXPECTED_FINAL_STATE
# $08:125239296
# $09:2000
# $29:0