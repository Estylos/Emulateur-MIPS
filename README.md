# Projet de CS351 - Émulateur MIPS
 
Émulateur d'assembleur MIPS codé en C dans le cadre du projet de CS351 (2022-2023) de troisième année à l'Esisar.

Auteurs : BERNARD Nathan, CADIC Esteban

Tous les fichiers de tests en assembleur ainsi le code machine en hexadécimal et l'état des registres attendus se trouvent dans le répertoire test/. 

Exécutez le programme sans argument afin de rentrer dans le mode interactif (EXIT pour quitter ce dernier).  
Exécutez le programme avec les arguments ``FICHIER_SOURCE -pas`` afin d’exécuter un programme assembleur en mode pas à pas avec affichage des registres et de la mémoire.
Exécutez le programme avec les arguments ``FICHIER_SOURCE SORTIE_ASSEMBLAGE SORTIE_REGISTRES`` afin d’exécuter un programme assembleur d'une traite et de sauvegarder dans des fichiers les instructions machines générées en hexadécimal en plus du contenu des registres.

Utilisez ``make tests`` pour lancer les tests automatiques.

## Crédits 

- Sujets et précisions apportés par L. Gonnord et S. Michelland  

- MIPS32® Architecture For Programmers Volume II, Revision 2.50 

- http://www.csbio.unc.edu/mcmillan/miniMIPS.html (simulateur MIPS en ligne par Leonard McMillan)

- http://mipsconverter.com/instruction.html (convertisseur d'instruction au format hexadécimal, par Aaron Wasserman)
