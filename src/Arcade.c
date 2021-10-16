/*
 * Arcade.c
 *
 *  Created on: 14 oct. 2021
 *      Author: Leandro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "Arcade.h"
#include "Playroom.h"

#define COUNTRY_AND_GAME_LEN 63
#define MESSAGE_LEN 100

//private prototypes
static int createId (void);
static int validateIfPlayroomIdExists (Playroom list[], int len, int id);
static int getPlayroomId (int* pPlayroomId, Playroom list[], int len);
static int getArcadeSoundType (int* pSoundType);
static int getArcadeNumberOfPlayers (int* pPlayers);
static int getArcadeMaxCoins (int* pMaxCoins);
static int getArcadeGame (char arcadeGame[]);
static int getArcadeCountry (char arcadeCountry[]);
static void printItems (void);

int arcade_init(Arcade list[], int len)
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

int arcade_add(Arcade* pArcade, Playroom list[], int len)
{
	int status = -1;
	char auxCountry[COUNTRY_AND_GAME_LEN];
	char auxGame[COUNTRY_AND_GAME_LEN];
	int auxMaxNumberOfCoins;
	int auxNumberOfPlayers;
	int auxSoundType;
	int auxIdPlayroom;

	if (pArcade != NULL)
	{
		if(getArcadeCountry(auxCountry) == 1)
		{
			if (getArcadeGame(auxGame) == 1)
			{
				if (getArcadeMaxCoins(&auxMaxNumberOfCoins) == 1)
				{
					if (getArcadeNumberOfPlayers(&auxNumberOfPlayers) == 1)
					{
						if (getArcadeSoundType(&auxSoundType) == 1)
						{
							if (getPlayroomId(&auxIdPlayroom, list, len) == 1)
							{
								strncpy(pArcade->country, auxCountry, COUNTRY_AND_GAME_LEN);
								strncpy(pArcade->game, auxGame, COUNTRY_AND_GAME_LEN);
								pArcade->maxNumberOfCoins = auxMaxNumberOfCoins;
								pArcade->numberOfPlayers = auxNumberOfPlayers;
								pArcade->soundType = auxSoundType;
								pArcade->idPlayroom = auxIdPlayroom;
								pArcade->isEmpty = -1;
								pArcade->id = createId();
								printf("\nDatos cargados correctamente");
								status = 1;
							}
							else
								printf("\nError el id de salon indicado no existe. Vuelva a cargar el arcade");
						}
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
		else
		{
			printf("\nHubo un error");
		}
	}

	return status;
}

int arcade_findAnEmptyPosition(Arcade list[], int listLen, int* pEmptyPosition)
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

int arcade_findById (Arcade list[], int listLen, int id, int* pFoundPosition)
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

int arcade_modifyNumberOfPlayers (Arcade* pArcade)
{
	int status = -1;
	int auxNumberOfPlayers;

	if (pArcade != NULL)
	{
		if (getArcadeNumberOfPlayers(&auxNumberOfPlayers) == 1)
		{
			pArcade->numberOfPlayers = auxNumberOfPlayers;
			status = 1;
		}
	}
	return status;
}

int arcade_modifyGame (Arcade* pArcade)
{
	int status = -1;
	char auxGame[COUNTRY_AND_GAME_LEN];

	if (pArcade != NULL)
	{
		if (getArcadeGame(auxGame) == 1)
		{
			strncpy(pArcade->game, auxGame, COUNTRY_AND_GAME_LEN);
			status = 1;
		}
	}
	return status;
}

int selectFieldToModify (int* selectedField)
{
	int status = -1;
	int auxSelectedItem;

	printItems();
	if (input_getInt(1, 2, 2, "Elija el campo a modificar", &auxSelectedItem, "Error") == 1)
	{
		status = 1;
		*selectedField = auxSelectedItem;
	}
	return status;
}

void arcade_printList(Arcade list[], int len)
{
	int index;

	for (index = 0; index < len; index++)
	{
		if (list[index].isEmpty != 1)
		{
			printf("\n----------------------------");
			printf("\nID: %d", list[index].id);
			printf("\nPAIS: %s", list[index].country);
			printf("\nJUEGO: %s", list[index].game);
			printf("\nMAXIMO NUMERO DE FICHAS: %d", list[index].maxNumberOfCoins);
			printf("\nNUMERO DE JUGADORES: %d", list[index].numberOfPlayers);
			printf("\nSONIDO: %d", list[index].soundType);
			printf("\nPERTENECE A SALON ID %d", list[index].idPlayroom);
		}
	}
}

void printArcadeWithRoomInfo (Arcade arcadesList[], int arcadeLen, Playroom playroomsList[], int roomLen)
{
	int index;
	int playroomId;
	int position;

	for (index = 0; index < arcadeLen; index++)
	{
		if (arcadesList[index].isEmpty != 1)
		{
			playroomId = arcadesList[index].idPlayroom;
			playroom_findById(playroomsList, roomLen, playroomId, &position);
			printf("\n----------------------------");
			printf("\nID: %d", arcadesList[index].id);
			printf("\nPAIS: %s", arcadesList[index].country);
			printf("\nJUEGO: %s", arcadesList[index].game);
			printf("\nMAXIMO NUMERO DE FICHAS: %d", arcadesList[index].maxNumberOfCoins);
			printf("\nNUMERO DE JUGADORES: %d", arcadesList[index].numberOfPlayers);
			printf("\nSONIDO: %d", arcadesList[index].soundType);
			printf("\nPERTENECE A SALON ID %d", playroomId);
			printf("\nNOMBRE DE SALON: %s", playroomsList[position].name);
			printf("\nDIRECCION DE SALON: %s", playroomsList[position].address);
			printf("\nTIPO DE SALON: %d", playroomsList[position].type);
		}
	}
}

void arcade_deleteByRoomId(Arcade arcadeList[], int arcadeListLen, int playroomId)
{
	int index;

	for (index = 0; index < arcadeListLen; index++)
	{
		if (arcadeList[index].isEmpty != 1 && arcadeList[index].idPlayroom == playroomId)
		{
			arcadeList[index].isEmpty = 1;
		}
	}
}

int arcade_deleteById(Arcade list[], int listLen, int id)
{
	int status = -1;
	int foundPosition;

	if (arcade_findById(list, listLen, id, &foundPosition) == 1)
	{
		status = 1;
		list[foundPosition].isEmpty = 1;
	}
	return status;
}

int arcade_validateIfIdExists (Arcade arcadeList[], int arcadeListLen, int arcadeId, int* arcadeIndex)
{
	int status = -1;
	int index;

	for (index = 0; index < arcadeListLen; index++)
	{
		if (arcadeList[index].isEmpty != 1)
		{
			if (arcadeList[index].id == arcadeId)
			{
				*arcadeIndex = index;
				status = 1;
				break;
			}
		}
	}
	return status;
}

static void printItems (void)
{
	printf("\n---------------------");
	printf("\n1. CANTIDAD DE JUGADORES");
	printf("\n2. JUEGO");
	printf("\n---------------------");
}

static int getArcadeCountry (char arcadeCountry[])
{
	int status = -1;
	char message[MESSAGE_LEN];
	char auxCountry[COUNTRY_AND_GAME_LEN];
	strncpy(message, "\n->Ingrese el país del arcade", MESSAGE_LEN);
	if (input_getText(auxCountry, COUNTRY_AND_GAME_LEN, 2, message, "Error") == 1)
	{
		status = 1;
		strncpy(arcadeCountry, auxCountry, COUNTRY_AND_GAME_LEN);
	}
	return status;
}

static int getArcadeGame (char arcadeGame[])
{
	int status = -1;
	char message[MESSAGE_LEN];
	char auxGame[COUNTRY_AND_GAME_LEN];
	strncpy(message, "\n->Ingrese el juego del arcade", MESSAGE_LEN);
	if (input_getText(auxGame, COUNTRY_AND_GAME_LEN, 2, message, "Error") == 1)
	{
		status = 1;
		strncpy(arcadeGame, auxGame, COUNTRY_AND_GAME_LEN);
	}
	return status;
}

static int getArcadeMaxCoins (int* pMaxCoins)
{
	int status = -1;
	char message[MESSAGE_LEN];
	int auxMaxCoins;
	strncpy(message, "\n->Ingrese el numero maximo de fichas (entre 1 y 100)", MESSAGE_LEN);
	if (input_getInt(1, 100, 2, message, &auxMaxCoins, "Error") == 1)
	{
		status = 1;
		*pMaxCoins = auxMaxCoins;
	}
	return status;
}

static int getArcadeNumberOfPlayers (int* pPlayers)
{
	int status = -1;
	char message[MESSAGE_LEN];
	int auxPlayers;
	strncpy(message, "\n->Ingrese la cantidad de jugadores (entre 1 y 4)", MESSAGE_LEN);
	if (input_getInt(1, 4, 2, message, &auxPlayers, "Error") == 1)
	{
		status = 1;
		*pPlayers = auxPlayers;
	}
	return status;
}

static int getArcadeSoundType (int* pSoundType)
{
	int status = -1;
	char message[MESSAGE_LEN];
	int auxSoundType;
	strncpy(message, "\n->Ingrese el tipo de sonido:\n1.Mono\n2.Estereo", MESSAGE_LEN);
	if (input_getInt(1, 2, 2, message, &auxSoundType, "Error") == 1)
	{
		status = 1;
		*pSoundType = auxSoundType;
	}
	return status;
}

static int getPlayroomId (int* pPlayroomId, Playroom list[], int len)
{
	int status = -1;
	char message[MESSAGE_LEN];
	int auxPlayroomId;
	strncpy(message, "\n->Ingrese el id del salón", MESSAGE_LEN);
	if (input_getInt(1, 9999, 2, message, &auxPlayroomId, "Error") == 1)
	{
		if (validateIfPlayroomIdExists(list, len, auxPlayroomId) == 1)
		{
			status = 1;
			*pPlayroomId = auxPlayroomId;
		}
	}
	return status;
}

static int validateIfPlayroomIdExists (Playroom list[], int len, int id)
{
	int exists = -1;
	int index;

	for (index = 0; index < len; index++)
	{
		if (list[index].isEmpty != 1 && list[index].id == id)
		{
			exists = 1;
			break;
		}
	}
	return exists;
}

static int createId (void)
{
	static int idCounter = 0;
	idCounter++;
	return idCounter;
}
