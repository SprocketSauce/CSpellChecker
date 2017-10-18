/*
 * FILE: config.h
 * AUTHOR: Jack McNair 18927430
 * LAST MOD: 10/18/2017
 *
 * Describes a struct containing configuration information.
 */

/*
 * Config
 *
 * A struct that stores configuration information.
 *
 * FIELDS:
 *  dict - Name of the dictionary file. Filenames have a maximum length of 40 characters
 *  maxDif - Maximum difference between a word and a suggested correction
 *  autoCorrect - 1 if autoCorrect is on, 0 if off
 */
typedef struct {
	char dict[41];
	int maxDif;
	int autoCorrect;
} Config;

Config* getConfig( void );
