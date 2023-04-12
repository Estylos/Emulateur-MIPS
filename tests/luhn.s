# Algo vérifiant un code de Luhn
# Le code a vérifier (max 16 bits) est mis dans $t0
# https://fr.wikipedia.org/wiki/Formule_de_Luhn

LUI $t9, 2048 # Valeur du SP
ADD $sp, $zero, $t9 # SP à 0x08000000

# Code à vérifier (le dernier chiffre est la clef)
# Ici, le SIREN l'Esisar : 193819125
LUI $t0, 2957
ADDI $t0, $t0, 29173 

ADDI $t1, $zero, 10 # Diviseur
ADDI $t2, $zero, -1 # Fin de chaîne
ADD $a0, $zero, $zero # Résultat du test de Luhn

SW $t2, 0($sp) # délimiteur début de chaîne
ADDI $sp, $sp, -4

# Mise en mémoire du code
# Boucle
DIV $t0, $t1
MFLO $t0 # Quotient (à casser)
MFHI $t3 # Reste (unité)

SW $t3, 0($sp) # On met en mémoire notre chiffre
ADDI $sp, $sp, -4

BGTZ $t0, -6 # Tant que $t0 (notre code) est >0 alors on boucle
NOP
# Fin boucle

ADDI $t2, $zero, -1
SW $t2, 0($sp) # délimiteur fin de chaîne
SW $t2, -4($sp) # on en met 2 car on va sauter de 2 en 2

ADD $sp, $zero, $t9 # SP à 0x08000000 (on revient en haut de la pile)
ADDI $sp, $sp, -8 # on revient à l'avant dernier chiffre

# Doubleur des chiffres impaires
LW $t0, 0($sp)

# Boucle
ADD $t0, $t0, $t0 # on multiplie notre chiffre par 2

DIV $t0, $t1
MFLO $t3 # Quotient 
MFHI $t0 # Reste
ADD $t0, $t0, $t3 # On ajoute le quotient et le reste

SW $t0, 0($sp) # On remet notre chiffre en mémoire

ADDI $sp, $sp, -8 # On revient 2 chiffres avant
LW $t0, 0($sp)
BGTZ $t0, -9 # Tant que $t0 n'est pas -1 on boucle
NOP
# Fin boucle

ADD $sp, $zero, $t9 # SP à 0x08000000 (on revient en haut de la pile)
ADDI $sp, $sp, -4 # on revient à l'avant dernier chiffre

# Addition de tous les chiffres
LW $t0, 0($sp)

# Boucle
ADD $a0, $a0, $t0

ADDI $sp, $sp, -4 
LW $t0, 0($sp) 
BGTZ $t0, -4 # Tant que $t0 n'est pas -1 on boucle
NOP
# Fin boucle

DIV $a0, $t1 # On va regarder si le reste est 0
MFHI $a0 # Reste

#
# Résultat : si $a0 est différent de 0 alors le code n'est pas en accord avec la formule de Luhn
#

# EXPECTED_ASSEMBLY
# 3C190800
# 0019E820
# 3C080B8D
# 210871F5
# 2009000A
# 200AFFFF
# 00002020
# AFAA0000
# 23BDFFFC
# 0109001A
# 00004012
# 00005810
# AFAB0000
# 23BDFFFC
# 1D00FFFA
# 00000000
# 200AFFFF
# AFAA0000
# AFAAFFFC
# 0019E820
# 23BDFFF8
# 8FA80000
# 01084020
# 0109001A
# 00005812
# 00004010
# 010B4020
# AFA80000
# 23BDFFF8
# 8FA80000
# 1D00FFF7
# 00000000
# 0019E820
# 23BDFFFC
# 8FA80000
# 00882020
# 23BDFFFC
# 8FA80000
# 1D00FFFC
# 00000000
# 0089001A
# 00002010

# EXPECTED_FINAL_STATE
# $08: -1
# $09: 10
# $10: -1
# $11: 1
# $25: 134217728
# $29: 134217688
# LO: 4