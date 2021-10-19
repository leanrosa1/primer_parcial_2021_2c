/*
 * input.c
 *
 *  Created on: 7 sep. 2021
 *      Author: Leandro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myStr.h"

int myGetS (char pCadena[], int lenCadena);

/**
 * \brief: Ask user a float within an specific range
 *
 * \param minValue: minimum allowed value
 * \param maxValue: maximum allowed value
 * \param retries: indicates how many retries the user has if makes an error
 * \param message: informative message to ask the number
 * \param *pNumber: float pointer to write user's input
 * \param errorMessage: error message if user makes more errors than allowed retries
 * \return 1 if OK // -1 if Error
 */
int input_getFloat (float minValue, float maxValue, int retries, char message[], float* pNumber, char errorMessage[])
{
	int counter;
	char number[64];
	float auxiliar;
	int status;
	int validationResult;
	if (minValue < maxValue && pNumber != NULL && retries > 0) {
		for (counter = 0; counter <= retries; counter++)
		{
			printf("%s \n", message);
			if (myGetS(number, sizeof(number)) == 1)
			{
				myStrIsFloat(number, &validationResult);
				if (validationResult == 1)
				{
					auxiliar = atof(number);
					if (auxiliar >= minValue && auxiliar <= maxValue)
					{
						*pNumber = auxiliar;
						status = 1;
						break;
					}
					else
					{
						status = 0;
						printf("\n%s \n", errorMessage);
					}
				}
				else
				{
					status = 0;
					printf("\n%s \n", errorMessage);
				}
			} else {
				status = 0;
				printf("\n%s \n", errorMessage);
			}
		}
	} else {
		status = 0;
		printf("\nNo hay mas reintentos.");
	}
	return status;
}

/**
 * \brief: Ask user an integer within an specific range
 *
 * \param minValue: minimum allowed value
 * \param maxValue: maximum allowed value
 * \param retries: indicates how many retries the user has if makes an error
 * \param message: informative message to ask the number
 * \param *pNumber: int pointer to write user's input
 * \param errorMessage: error message if user makes more errors than allowed retries
 * \return 1 if OK // -1 if Error
 */
int input_getInt (int minValue, int maxValue, int retries, char message[], int* pNumber, char messageError[]) {
	int counter;
	char number[16];
	int auxiliar;
	int status;
	int validationResult;
	if (minValue < maxValue && pNumber != NULL && retries > 0) {
		for (counter = 0; counter <= retries; counter++)
		{
			printf("\n%s \n", message);
			if (myGetS(number, sizeof(number)) == 1)
			{
				myStrIsOnlyNumbers(number, &validationResult);
				if (validationResult == 1)
				{
					auxiliar = atoi(number);
					if (auxiliar >= minValue && auxiliar <= maxValue)
					{
						*pNumber = auxiliar;
						status = 1;
						break;
					}
					else
					{
						status = -1;
						printf("\n%s \n", messageError);
					}
				}
				else
				{
					status = -1;
					printf("\n%s \n", messageError);
				}
			} else {
				status = -1;
				printf("\n%s \n", messageError);
			}
		}
	} else {
		status = -1;
		printf("\n%s \n", messageError);
	}
	return status;
}

/**
 * \brief: Ask user a float
 *
 * \param retries: indicates how many retries the user has if makes an error
 * \param message: informative message to ask the number
 * \param *pNumber: float pointer to write user's input
 * \param errorMessage: error message if user makes more errors than allowed retries
 * \return 1 if OK // -1 if Error
 */
int input_getFloatWithoutRange (char message[], char errorMessage[], int retries, float* pNumber) {
	int remainingAttempts;
	int counter;
	int status;
	float auxiliar;
	for (counter = 0; counter <= retries; counter++)
	{
		printf("\n%s \n", message);
		fflush(stdin);
		if (scanf("%f", &auxiliar) == 1) {
			*pNumber = auxiliar;
			status = 1;
			break;
		} else {
			status = 0;
			remainingAttempts = retries - counter;
			printf("Error, te quedan %d intentos", remainingAttempts);
		}
	}
	return status;
}

/**
 * \brief: Ask user a character string
 *
 * \param pString: char pointer to write user's input
 * \param len: char pointer's len
 * \param retries: indicates how many retries the user has if makes an error
 * \param message: informative message to ask the text
 * \param errorMessage: error message if user makes more errors than allowed retries
 * \return 1 if OK // -1 if Error
 */
int input_getText (char pString[], int len, int retries, char message[], char errorMessage[]) {
	int status;
	int counter;

	for (counter = 0; counter <= retries; counter++)
	{
		printf("\n%s \n", message);
		fflush(stdin);
		if (myGetS(pString, len) == 1)
		{
			status = 1;
			break;
		}
	}
	return status;
}

int myGetS (char pString[], int len)
{
	int status;
	int finalIndex;
	fflush(stdin);
	if (fgets(pString, len, stdin) != NULL) {
		finalIndex = myStrLen(pString) - 1;
		if (pString[finalIndex] == '\n')
		{
			pString[finalIndex] = '\0';
		}
		status = 1;
	} else {
		status = -1;
	}
	return status;
}



