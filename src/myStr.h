/*
 * myStr.h
 *
 *  Created on: 23 sep. 2021
 *      Author: Leandro
 */

#ifndef MYSTR_H_
#define MYSTR_H_
int myStrLen (char myStr[]);
int myStrCopy (char toStr[], char fromStr[]);
int myStrPuts (char myStr[]);
int myStrFindMayus (char myStr[]);
int myStrIsOnlyText (char myStr[], int* result);
int myStrIsOnlyNumbers (char myStr[], int* result);
int myStrIsAlphanumeric (char myStr[], int* result);
int myStrIsFloat (char myStr[], int* result);
#endif /* MYSTR_H_ */
