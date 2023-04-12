# Algo vérifiant la conjoncture de Syracuse
# https://fr.wikipedia.org/wiki/Conjecture_de_Syracuse

ADDI $t0, $0, 15 # Nombre de départ

ADDI $t1, $0, 2 # Servant à la division
ADDI $t2, $0, 3 # Servant à la multiplication (cas impaire)
ADDI $t3, $0, 1 # Nombre à atteindre
ADDI $a0, $0, 0 # Rang du 1er '1' dans le suite de Syracuse pour u_0 = $t0

# Boucle principale
BEQ $t0, $t3, 14 # Si on a atteint 1, on termine
NOP

ADDI $a0, $a0, 1 # On incrémente de 1 le rang
DIV $t0, $t1
MFHI $t4 # Reste
MFLO $t5 # Quotient

BLEZ $t4, 6 # Si le nombre est paire on saute
NOP

# Le nombre est impaire
MULT $t0, $t2 # On multiplie notre nombre par 3
MFLO $t0 # On récupère les 32 premiers bits du résultats
ADDI $t0, $t0, 1 # On ajoute 1
J 5
NOP

# Le nombre est paire
ADD $t0, $zero, $t5 # On met le résultat de la division de $t0 par 2 dans $t0
J 5
NOP

# EXPECTED_ASSEMBLY
# 2008000F
# 20090002
# 200A0003
# 200B0001
# 20040000
# 110B000E
# 00000000
# 20840001
# 0109001A
# 00006010
# 00006812
# 19800006
# 00000000
# 010A0018
# 00004012
# 21080001
# 08000005
# 00000000
# 000D4020
# 08000005
# 00000000

# EXPECTED_FINAL_STATE
# $04: 17
# $08: 1
# $09: 2
# $10: 3
# $11: 1
# $13: 1
# LO: 1
