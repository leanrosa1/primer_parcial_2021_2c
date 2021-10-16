/*
 * myStr.c
 *
 *  Created on: 23 sep. 2021
 *      Author: Leandro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myStrLen (char myStr[])
{
	int len = - 1;
	int index;

	if (myStr != NULL)
	{
		for (index = 0;; index++)
		{
			if (myStr[index] == '\0' && index != 0)
			{
				len = index;
				break;
			}
		}
	}
	return len;
}

int myStrCopy (char toStr[], char fromStr[])
{
	int status = -1;
	if (toStr != NULL)
	{
		int index;
		int fromStrSize = myStrLen(fromStr);
		for (index = 0; index <= fromStrSize; index++)
		{
			toStr[index] = fromStr[index];
		}
		status = 1;
	}
	return status;
}

int myStrPuts (char myStr[])
{
	int status = -1;
	if (myStr != NULL)
	{
		int index = 0;
		do
		{
			printf("%c", myStr[index]);
			index++;
		} while (myStr[index] != '\0');
		status = 1;
	}
	return status;
}

int myStrFindMayus (char myStr[])
{
	int status = -1;
	int index = 0;
	int mayusCounter = 0;
	if (myStr != NULL)
	{
		while (myStr[index] != '\0')
		{
			if (myStr[index] >= 'A' && myStr[index]  <= 'Z')
			{
				mayusCounter++;
			}
			index ++;
		}
		printf("La cantidad de mayúsculas es %d", mayusCounter);
		status = 1;
	}
	return status;
}

int myStrIsOnlyText (char myStr[], int* result)
{
	int status = -1;
	int index = 0;
	int isText = 1;

	if (myStr != NULL)
	{
		status = 1;
		while (myStr[index] != '\0')
		{
			if (myStr[index] > 122)
			{
				isText = -1;
				break;
			} else if (myStr[index] < 65 && myStr[index] != 32)
			{
				isText = -1;
				break;
			}
			index++;
		}
		*result = isText;
	}
	return status;
}

int myStrIsOnlyNumbers (char myStr[], int* result)
{
	int status = -1;
	int index = 0;
	int isNumber = 1;

	if (myStr != NULL)
	{
		status = 1;
		while (myStr[index] != '\0')
		{
			if (myStr[index] < 48 || myStr[index] > 57)
			{
				if (myStr[index] != 32)
				{
					isNumber = -1;
					break;
				}
			}
			index++;
		}
		*result = isNumber;
	}
	return status;
}

int myStrIsAlphanumeric (char myStr[], int* result)
{
	int status = - 1;
	int index = 0;
	int isNumeric = -1;
	int isText = - 1;

	if (myStr != NULL)
	{
		status = 1;
		while (myStr[index] != '\0')
		{
			if (myStr[index] > 47 && myStr[index] < 58)
			{
				isNumeric = 1;
			}
			else if (myStr[index] > 64 && myStr[index] < 123)
			{
				isText = 1;
			}
			else
			{
				if (myStr[index] != 32)
				{
					isNumeric = -1;
					isText = -1;
					break;
				}
			}
			index++;
		}

		if(isNumeric == 1 && isText == 1)
		{
			*result = 1;
		}
		else
		{
			*result = -1;
		}
	}
	return status;
}

int myStrIsFloat (char myStr[], int* result)
{
	int status = -1;
	int index = 0;
	int isNumber = 1;
	int dotCounter = 0;

	if (myStr != NULL)
	{
		status = 1;
		while (myStr[index] != '\0')
		{
			if (myStr[index] < 48 || myStr[index] > 57)
			{
				if (myStr[index] != '.')
				{
					isNumber = -1;
					break;
				}
				else
				{
					dotCounter++;
					if (dotCounter > 1)
					{
						isNumber = -1;
						break;
					}
				}
			}
			index++;
		}
		*result = isNumber;
	}
	return status;
}
