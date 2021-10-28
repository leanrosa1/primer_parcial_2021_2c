/*
 * Playroom.c
 *
 *  Created on: 14 oct. 2021
 *      Author: Leandro
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "Playroom.h"

#define NAME_AND_ADDRESS_LEN 64
#define MESSAGE_LEN 100

//private prototypes
static int getPlayroomName (char playroomName[]);
static int getPlayroomAddress (char playroomAddress[]);
static int getPlayroomType (int* pType);
static int createId (void);
static void printItems (void);
static int selectFieldToModify (int* selectedField);

/**
 * \brief: Put every playroom's isEmpty flag in 1

 * \param list: a Playroom array
 * \param len: length of the array
 * \return 1 if OK // -1 if Error
 */
int playroom_init(Playroom list[], int len)
{
	int status = -1;
	int index;

	if (list != NULL && len > 0)
	{
		status = 0;
		for (index = 0; index < len; index++)
		{
			list[index].isEmpty = 1;
		}
	}
	return status;
}

void playroom_forceAdd (Playroom* pPlayroom)
{
	pPlayroom->id = createId();
	strncpy(pPlayroom->name, "Salon", NAME_AND_ADDRESS_LEN);
	strncpy(pPlayroom->address, "Mitre 5469", NAME_AND_ADDRESS_LEN);
	pPlayroom->type = 1;
	pPlayroom->isEmpty = -1;
}

/**
 * \brief: Ask user to fill all playroom struct fields.
 * This function put flag is empty in -1 and write an id for the new playroom

 * \param pArcade: a Playroom variable pointer
 * \return 1 if OK // -1 if Error
 */
int playroom_add(Playroom* pPlayroom)
{
	int status = -1;
	char auxName[NAME_AND_ADDRESS_LEN];
	char auxAddress[NAME_AND_ADDRESS_LEN];
	int auxType;

	if (pPlayroom != NULL)
	{
		if(getPlayroomName(auxName) == 1)
		{
			if (getPlayroomAddress(auxAddress) == 1)
			{
				if (getPlayroomType(&auxType) == 1)
				{
					strncpy(pPlayroom->name, auxName, NAME_AND_ADDRESS_LEN);
					strncpy(pPlayroom->address, auxAddress, NAME_AND_ADDRESS_LEN);
					pPlayroom->type = auxType;
					pPlayroom->isEmpty = -1;
					pPlayroom->id = createId();
					printf("\nDatos cargados correctamente");
					printf("\n----------------------------------");
					printf("\nID: %d", pPlayroom->id);
					printf("\nNOMBRE: %s", pPlayroom->name);
					printf("\nDIRECCION: %s", pPlayroom->address);
					printf("\nTIPO: %d", pPlayroom->type);
					printf("\n----------------------------------");
					status = 1;
				}
				else
				{
					printf("\nHubo un error");
				}
			}
			else
			{
				printf("\nHubo un error");
			}
		}
		else
		{
			printf("\nHubo un error");
		}
	}

	return status;
}

/**
 * \brief: Search and return by reference first empty position (if exists) in Playroom structs array
 *
 * \param list: an array of Playroom structs
 * \param listLen: length of Playroom array
 * \param pEmptyPosition: int pointer to write the empty position
 * \return 1 if OK // -1 if Error or not empty position found
 */
int playroom_findAnEmptyPosition(Playroom list[], int listLen, int* pEmptyPosition)
{
	int index;
	int status = -1;
	if (list != NULL && listLen > 0)
	{
		for (index = 0; index < listLen; index++)
		{
			if (list[index].isEmpty == 1)
			{
				*pEmptyPosition = index;
				status = 1;
				break;
			}
		}
	}
	return status;
}

/**
 * \brief: Search and return by reference the position (if exists) of an specific playroom in Playroom structs array
 *
 * \param list: an array of Playroom structs
 * \param listLen: length of Playroom array
 * \param id: ID of the playroom
 * \param pFoundPosition: int pointer to write the position (if exists) of the arcade in Playroom structs array
 * \return 1 if OK // -1 if Error or not empty position found
 */
int playroom_findById (Playroom list[], int listLen, int id, int* pFoundPosition)
{
	int index;
	int status = -1;
	if (list != NULL && listLen > 0)
	{
		*pFoundPosition = -1;
		status = 1;
		for (index = 0; index < listLen; index++)
		{
			if (list[index].isEmpty != 1)
			{
				if (list[index].id == id)
				{
					*pFoundPosition = index;
					break;
				}
			}
		}
	}
	return status;
}

/**
 * \brief: Ask user which field wants to modify. Allow fields: name, address, type.

 * \param pArcade: a Playroom variable pointer
 * \return 1 if OK // -1 if Error
 */
int playroom_modify (Playroom* pPlayroom)
{
	int status = -1;
	int fieldToModify;
	char auxName[NAME_AND_ADDRESS_LEN];
	char auxAddress[NAME_AND_ADDRESS_LEN];
	int auxType;

	if (pPlayroom != NULL)
	{
		if (selectFieldToModify(&fieldToModify) == 1)
		{
			status = 1;
			switch (fieldToModify)
			{
				case 1:
					if (getPlayroomName(auxName) == 1)
					{
						strncpy(pPlayroom->name, auxName, NAME_AND_ADDRESS_LEN);
					}
					break;
				case 2:
					if (getPlayroomAddress(auxAddress) == 1)
					{
						strncpy(pPlayroom->address, auxAddress, NAME_AND_ADDRESS_LEN);
					}
					break;
				case 3:
					if (getPlayroomType(&auxType) == 1)
					{
						pPlayroom->type = auxType;
					}
					break;
			}
		}
	}
	return status;
}

/**
 * \brief: Deleted an specific playroom of given playrooms list
 *
 * \param list: an array of Playroom structs
 * \param listLen: length of Playroom array
 * \param id: ID of the playroom
 * \return 1 if OK // -1 if Error
 */
int playroom_deleteById(Playroom list[], int listLen, int id)
{
	int status = -1;
	int foundPosition;
	if (playroom_findById(list, listLen, id, &foundPosition) == 1)
	{
		status = 1;
		list[foundPosition].isEmpty = 1;
	}
	return status;
}

/**
 * \brief: ASk user a playroom ID
 *
 * \param pId: int pointer to write user's input
 * \return 1 if OK // -1 if Error
 */
int playroom_getId (int* pId)
{
	int status = -1;
	int auxId;

	if (input_getInt(1, 9999, 2, "\n->Ingrese el id del salon", &auxId, "Error") == 1)
	{
		*pId = auxId;
		status = 1;
	}
	return status;
}

/**
 * \brief: Print every active playrooms in playrooms array. If printType == 1, function will print playroom type too.
 *
 * \param list: an array of Playroom structs
 * \param len: length of Playroom array
 * \param printType: 1 if wants to print playroom type
 * \return 1 if OK // -1 if Error
 */
void playroom_printList(Playroom list[], int len, int printType)
{
	int index;

	for (index = 0; index < len; index++)
	{
		if (list[index].isEmpty != 1)
		{
			printf("\n-----------------------------------------------");
			printf("\nID: %d", list[index].id);
			printf("\nNOMBRE: %s", list[index].name);
			printf("\nDIRECCION: %s", list[index].address);
			if (printType == 1)
			{
				printf("\nTIPO: %d", list[index].type);
			}
		}
	}
}

/**
 * \brief: Ask user the field of a Playroom to modify (option 1, option 2 or option 3)
 *
 * \param selectedField: int pointer to write chosen option
 * \return 1 if OK // -1 if Error
 */
static int selectFieldToModify (int* selectedField)
{
	int status = -1;
	int auxSelectedItem;

	printItems();
	if (input_getInt(1, 3, 2, "Elija el campo a modificar", &auxSelectedItem, "Error") == 1)
	{
		status = 1;
		*selectedField = auxSelectedItem;
	}
	return status;
}

/**
 * \brief: Print choose option to modify menu
 */
static void printItems (void)
{
	printf("\n---------------------");
	printf("\n1. NOMBRE");
	printf("\n2. DIRECCION");
	printf("\n3. TIPO");
	printf("\n---------------------");
}

/**
 * \brief: Ask user the name of a Playroom
 *
 * \param playroomName: char pointer to write user's input
 * \return 1 if OK // -1 if Error
 */
static int getPlayroomName (char playroomName[])
{
	int status = -1;
	char message[MESSAGE_LEN];
	char auxName[NAME_AND_ADDRESS_LEN];
	strncpy(message, "\n->Ingrese el nombre del salón", MESSAGE_LEN);
	if (input_getText(auxName, NAME_AND_ADDRESS_LEN, 2, message, "Error") == 1)
	{
		status = 1;
		strncpy(playroomName, auxName, NAME_AND_ADDRESS_LEN);
	}
	return status;
}

/**
 * \brief: Ask user the address of a Playroom
 *
 * \param playroomAddress: char pointer to write user's input
 * \return 1 if OK // -1 if Error
 */
static int getPlayroomAddress (char playroomAddress[])
{
	int status = -1;
	char message[MESSAGE_LEN];
	char auxAddress[NAME_AND_ADDRESS_LEN];
	strncpy(message, "\n->Ingrese la dirección del salón", MESSAGE_LEN);
	if (input_getText(auxAddress, NAME_AND_ADDRESS_LEN, 2, message, "Error") == 1)
	{
		status = 1;
		strncpy(playroomAddress, auxAddress, NAME_AND_ADDRESS_LEN);
	}
	return status;
}

/**
 * \brief: Ask user the type of a Playroom
 *
 * \param pType: int pointer to write user's input
 * \return 1 if OK // -1 if Error
 */
static int getPlayroomType (int* pType)
{
	int status = -1;
	char message[MESSAGE_LEN];
	int auxType;
	strncpy(message, "\n->Ingrese el tipo de salón:\n1.Shopping\n2.Local", MESSAGE_LEN);
	if (input_getInt(1, 2, 2, message, &auxType, "Error") == 1)
	{
		status = 1;
		*pType = auxType;
	}
	return status;
}

/**
 * \brief: Create an auto increment ID for arcades
 *
 * \return ID
 */
static int createId (void)
{
	static int idCounter = 0;
	idCounter++;
	return idCounter;
}
