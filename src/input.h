/*
 * input.h
 *
 *  Created on: 7 sep. 2021
 *      Author: Leandro
 */

#ifndef INPUT_H_
#define INPUT_H_
int input_getFloat (float minValue, float maxValue, int retries, char message[], float* pNumber, char errorMessage[]);
int input_getInt (int minValue, int maxValue, int retries, char message[], int* pNumber, char messageError[]);
int input_getFloatWithoutRange (char message[], char errorMessage[], int retries, float* pNumber);
int input_getText (char pString[], int len, int retries, char message[], char errorMessage[]);
int myGetS (char pString[], int len);
int input_getEmployeeFields (char pName[], char pLastName[], float* pSalary, int* pSector);
#endif /* INPUT_H_ */
