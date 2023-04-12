/**
 * @file util.h
 * @author Nathan BERNARD, Esteban CADIC
 * @brief En tête du programme de fonctions outils utiles à d'autres programmes.
 * @copyright Sous licence MIT
 * 
 */
#ifndef __UTIL_H__
#define __UTIL_H__


/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

/** 
 * @addtogroup ANSI_CODE
 * Codes ANSI afin d'embellir le formatage.
 * @{
 */
#define ANSI_CODE_RESET      "\033[00m"
#define ANSI_CODE_BOLD       "\033[1m"
#define ANSI_CODE_DARK       "\033[2m"
#define ANSI_CODE_UNDERLINE  "\033[4m"
#define ANSI_CODE_BLINK      "\033[5m"
#define ANSI_CODE_REVERSE    "\033[7m"
#define ANSI_CODE_CONCEALED  "\033[8m"
#define ANSI_CODE_GREY       "\033[30m"
#define ANSI_CODE_RED        "\033[31m"
#define ANSI_CODE_GREEN      "\033[32m"
#define ANSI_CODE_YELLOW     "\033[33m"
#define ANSI_CODE_BLUE       "\033[34m"
#define ANSI_CODE_MAGENTA    "\033[35m"
#define ANSI_CODE_CYAN       "\033[36m"
#define ANSI_CODE_WHITE      "\033[37m"
#define ANSI_CODE_BG_GREY    "\033[40m"
#define ANSI_CODE_BG_RED     "\033[41m"
#define ANSI_CODE_BG_GREEN   "\033[42m"
#define ANSI_CODE_BG_YELLOW  "\033[43m"
#define ANSI_CODE_BG_BLUE    "\033[44m"
#define ANSI_CODE_BG_MAGENTA "\033[45m"
#define ANSI_CODE_BG_CYAN    "\033[46m"
#define ANSI_CODE_BG_WHITE   "\033[47m"
/** @} */

/**
 * @brief Macro servant à loguer une erreur (précisez uniquement la chaîne).
 */
#define LOG_ERROR(...) error(__FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Macro servant à loguer une erreur de simulation (précisez uniquement la chaîne).
 */
#define LOG_RUNTIME_ERROR(...) runtimeError(__FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Macro servant à loguer un avertissement (précisez uniquement la chaîne).
 */
#define LOG_WARN(...)  warning(__FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Macro servant à loguer du debug (précisez uniquement la chaîne).
 */
#ifdef __DEBUG__
	#define LOG_DEBUG(...)  debug(__FILE__, __LINE__, __VA_ARGS__)
#else
	#define LOG_DEBUG(...)
#endif
/**
 * @brief Macro servant à générer une erreur si un nombre n'est pas compris dans un interval.
 */
#define LOG_ERROR_NB_INTERVAL(X, A, B, ...) (((X) < (A) || (X) > (B)) ? error(__FILE__, __LINE__, __VA_ARGS__) : 0)


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à loguer une erreur.
 * 
 * @param file Chemin d'accès du fichier source C
 * @param line Ligne du fichier où la fonction est appelée
 * @param fmt Chaîne de caractères formatée décrivant l'erreur
 */
extern void error(const char *file, int line, const char *fmt, ...);

/**
 * @brief Fonction servant à loguer une erreur de simulation (runtime error).
 * 
 * @param file Chemin d'accès du fichier source C
 * @param line Ligne du fichier où la fonction est appelée
 * @param fmt Chaîne de caractères formatée décrivant l'erreur
 */
extern void runtimeError(const char *file, int line, const char *fmt, ...);

/**
 * @brief Fonction servant à loguer un avertissement.
 * 
 * @param file Chemin d'accès du fichier source C
 * @param line Ligne du fichier où la fonction est appelée
 * @param fmt Chaîne de caractères formatée décrivant l'avertissement
 */
extern void warning(const char *file, int line, const char *fmt, ...);

/**
 * @brief Fonction servant à loguer du debug.
 * 
 * @param file Chemin d'accès du fichier source C
 * @param line Ligne du fichier où la fonction est appelée
 * @param fmt Chaîne de caractères formatée décrivant le debug
 */
extern void debug(const char *file, int line, const char *fmt, ...);

/**
 * @brief Fonction malloc avec gestion de pointeur null.
 * 
 * @param n Taille du bloc mémoire
 */
extern void *emalloc(unsigned int n);

/**
 * @brief Fonction realloc avec gestion de pointeur null.
 * 
 * @param q Adresse du bloc mémoire à réallouer 
 * @param n Taille du bloc mémoire
 */
extern void *erealloc(void *q, unsigned int n);

/**
 * @brief Fonction fopen avec gestion de pointeur null.
 * 
 * @param pathname Chemin d'accès du fichier
 * @param mode Mode d'ouverture du fichier
 */
extern FILE *efopen(const char *pathname, const char *mode);

/**
 * @brief Fonction strtok avec gestion de pointeur null.
 * 
 * @param string Chaîne de caractères
 * @param delimiters Caractères de sépération à utiliser pour le découpage
 */
extern char *estrtok(char *string, const char *delimiters);


#endif