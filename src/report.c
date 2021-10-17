/*
 * report.c
 *
 *  Created on: 17 oct. 2021
 *      Author: Leandro
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arcade.h"
#include "Game.h"
#include "Playroom.h"

#define PLAYROOM_NAME_LEN 64
#define GAME_NAME_LEN 63

//private prototypes
int hasThisRoomOverFourArcades (Arcade arcadesList[], int arcadesListLen, int roomId);
void getPlayroomNameById (Playroom playroomsList[], int playroomsListLen, int playroomId, char playroomName[]);
int getNumberOfArcadesByPlayroomId (Arcade arcadesList[], int arcadesListLen, int playroomId);
int getArcadesByPlayroomId (Arcade arcadesList[], int arcadesListLen, int playroomId);
void getMaxNumberOfArcadesPlayroom (Playroom playroomsList[], int playroomsListLen);

int report_playroomsOverFourArcades (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen)
{
	int status = -1;
	int index;
	int roomId;
	int counter = 0;

	if (playroomsList != NULL && arcadesList != NULL && playroomsListLen > 0 && arcadesListLen > 0)
	{
		for (index = 0; index < playroomsListLen; index++)
		{
			if (playroomsList[index].isEmpty != 1)
			{
				roomId = playroomsList[index].id;
				if (hasThisRoomOverFourArcades(arcadesList, arcadesListLen, roomId) == 1)
				{
					printf("\n--------------------------------------------------");
					printf("\nID: %d", playroomsList[index].id);
					printf("\nNOMBRE: %s", playroomsList[index].name);
					printf("\nDIRECCION: %s", playroomsList[index].address);
					printf("\nTIPO DE SALON: %d", playroomsList[index].type);
					counter++;
				}
			}
		}
		if (counter == 0)
		{
			printf("\nNo hay salones con más de cuatro arcades");
		}
		status = 1;
	}
	return status;
}

int report_arcadesOverTwoPlayers (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen)
{
	int status = -1;
	int index;
	char playroomName[PLAYROOM_NAME_LEN];
	int playroomId;
	int counter = 0;

	if (playroomsList != NULL && arcadesList != NULL && playroomsListLen > 0 && arcadesListLen > 0)
	{
		for (index = 0; index < arcadesListLen; index++)
		{
			if (arcadesList[index].isEmpty != 1 && arcadesList[index].numberOfPlayers > 2)
			{
				playroomId = arcadesList[index].idPlayroom;
				getPlayroomNameById(playroomsList, playroomsListLen, playroomId, playroomName);
				printf("\n------------------------------------");
				printf("\nID: %d",arcadesList[index].id);
				printf("\nCANTIDAD DE JUGADORES: %d", arcadesList[index].numberOfPlayers);
				printf("\nJUEGO: %s", arcadesList[index].game);
				printf("\nNOMBRE DEL SALON: %s", playroomName);
				counter++;
			}
		}
		if (counter == 0)
		{
			printf("\nNo hay arcades de más de dos jugadores");
		}
		status = 1;
	}

	return status;
}

int report_playroomById (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int playroomId)
{
	int status = -1;
	int index;
	int numberOfArcades;

	if (playroomsList != NULL && arcadesList != NULL && playroomsListLen > 0 && arcadesListLen > 0 && playroomId > 0)
	{
		for (index = 0; index < playroomsListLen; index++)
		{
			if (playroomsList[index].isEmpty != 1 && playroomsList[index].id == playroomId)
			{
				numberOfArcades = getNumberOfArcadesByPlayroomId(arcadesList, arcadesListLen, playroomId);
				printf("\n--------------------------------");
				printf("\nNOMBRE: %s", playroomsList[index].name);
				printf("\nTIPO: %d", playroomsList[index].type);
				printf("\nDIRECCION: %s", playroomsList[index].address);
				printf("\nCANTIDAD DE ARCADES: %d", numberOfArcades);
				status = 1;
				break;
			}
		}
	}
	return status;
}

int report_arcadesByPlayroomId (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int playroomId)
{
	int status = -1;
	int index;

	if (playroomsList != NULL && arcadesList != NULL && playroomsListLen > 0 && arcadesListLen > 0 && playroomId > 0)
	{
		for (index = 0; index < playroomsListLen; index++)
		{
			if (playroomsList[index].isEmpty != 1 && playroomsList[index].id == playroomId)
			{

				if (getArcadesByPlayroomId(arcadesList, arcadesListLen, playroomId) > 0)
				{
					printf("\n---------------------------------");
					printf("\nNOMBRE DEL SALON: %s", playroomsList[index].name);
					printf("\nTIPO DE SALON: %d", playroomsList[index].type);
				}
				else
				{
					printf("\nEste salon no tiene arcades");
				}
				status = 1;
				break;
			}
		}
	}
	return status;
}

int report_maxNumberOfArcadesPlayroom (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen)
{
	int status = -1;
	int index;
	int playroomId;

	if (playroomsList != NULL && arcadesList != NULL && playroomsListLen > 0 && arcadesListLen > 0)
	{
		for (index = 0; index < playroomsListLen; index++)
		{
			if (playroomsList[index].isEmpty != 1)
			{
				playroomId = playroomsList[index].id;
				playroomsList[index].numberOfArcades = getNumberOfArcadesByPlayroomId(arcadesList, arcadesListLen, playroomId);
			}
		}
		getMaxNumberOfArcadesPlayroom(playroomsList, playroomsListLen);
		status = 1;
	}
	return status;
}

int report_maxAmountOfPlayroom (Arcade arcadesList[], int arcadesListLen, int playroomId, float coinPrice)
{
	int status = -1;
	int index;
	int numberOfCoins = 0;
	float totalAmount;

	if (arcadesList != NULL && arcadesListLen > 0 && playroomId > 0 && coinPrice > 0)
	{
		for (index = 0; index < arcadesListLen; index++)
		{
			if (arcadesList[index].isEmpty != 1 && arcadesList[index].idPlayroom == playroomId)
			{
				numberOfCoins += arcadesList[index].maxNumberOfCoins;
			}
		}
		totalAmount = numberOfCoins * coinPrice;
		printf("\n-------------------------------------------------------------------------------");
		printf("\nEl monto máximo que puede recaudar el salón con id %d es: %f", playroomId, totalAmount);
		printf("\n-------------------------------------------------------------------------------");
		status = 1;
	}
	return status;
}

int report_howManyArcadesHasThisGame (Arcade arcadesList[], int arcadesListLen, char gameName[])
{
	int status = -1;
	int index;
	int counter = 0;

	if (arcadesList != NULL && gameName != NULL && arcadesListLen > 0)
	{
		for (index = 0; index < arcadesListLen; index++)
		{
			if (arcadesList[index].isEmpty != 1)
			{
				if (strncmp(arcadesList[index].game, gameName, GAME_NAME_LEN) == 0)
				{
					counter++;
				}
			}
		}
		printf("\n-------------------------------------------------------------------------");
		printf("\nAl juego '%s' lo contienen %d arcades", gameName, counter);
		printf("\n-------------------------------------------------------------------------");
		status = 1;
	}

	return status;
}

void getMaxNumberOfArcadesPlayroom (Playroom playroomsList[], int playroomsListLen)
{
	int index;
	int biggerNumberOfArcades;
	int indexPlayroomBiggerNumberOfArcades;
	int counter = 0;

	for (index = 0; index < playroomsListLen; index++)
	{
		if (playroomsList[index].isEmpty != 1)
		{
			if (counter > 0)
			{
				if (playroomsList[index].numberOfArcades > biggerNumberOfArcades)
				{
					biggerNumberOfArcades = playroomsList[index].numberOfArcades;
					indexPlayroomBiggerNumberOfArcades = index;
				}
			}
			else
			{
				biggerNumberOfArcades = playroomsList[index].numberOfArcades;
				indexPlayroomBiggerNumberOfArcades = index;
				counter++;
			}
		}
	}
	printf("\n----------------------------------");
	printf("\nEl salon con mayor cantidad de arcades es el siguiente:");
	printf("\nID: %d", playroomsList[indexPlayroomBiggerNumberOfArcades].id);
	printf("\nNOBMRE: %s", playroomsList[indexPlayroomBiggerNumberOfArcades].name);
	printf("\nDIRECCION: %s", playroomsList[indexPlayroomBiggerNumberOfArcades].address);
	printf("\nTIPO: %d", playroomsList[indexPlayroomBiggerNumberOfArcades].type);
	printf("\nCANTIDAD DE ARCADES: %d", playroomsList[indexPlayroomBiggerNumberOfArcades].numberOfArcades);
}

int getArcadesByPlayroomId (Arcade arcadesList[], int arcadesListLen, int playroomId)
{
	int index;
	int counter = 0;

	for (index = 0; index < arcadesListLen; index++)
	{
		if (arcadesList[index].isEmpty != 1 && arcadesList[index].idPlayroom == playroomId)
		{
			printf("\n----------------------------------------------------");
			printf("\nID ARCADE: %d", arcadesList[index].id);
			printf("\nPAIS: %s", arcadesList[index].country);
			printf("\nJUEGO: %s", arcadesList[index].game);
			printf("\nCANTIDAD MAXIMA DE FICHAS: %d", arcadesList[index].maxNumberOfCoins);
			printf("\nCANTIDAD DE JUGADORES: %d", arcadesList[index].numberOfPlayers);
			printf("\nTIPO DE SONIDO: %d", arcadesList[index].soundType);
			counter++;
		}
	}
	return counter;
}

int getNumberOfArcadesByPlayroomId (Arcade arcadesList[], int arcadesListLen, int playroomId)
{
	int numberOfArcades = 0;
	int index;

	for (index = 0; index < arcadesListLen; index++)
	{
		if (arcadesList[index].isEmpty != 1 && arcadesList[index].idPlayroom == playroomId)
		{
			numberOfArcades++;
		}
	}
	return numberOfArcades;
}

void getPlayroomNameById (Playroom playroomsList[], int playroomsListLen, int playroomId, char playroomName[])
{
	int index;

	for (index = 0; index < playroomsListLen; index++)
	{
		if (playroomsList[index].isEmpty != 1 && playroomsList[index].id == playroomId)
		{
			strncpy(playroomName, playroomsList[index].name, PLAYROOM_NAME_LEN);
			break;
		}
	}
}

int hasThisRoomOverFourArcades (Arcade arcadesList[], int arcadesListLen, int roomId)
{
	int hasMoreThanFourArcades = -1;
	int counter = 0;
	int index;

	for (index = 0; index < arcadesListLen; index++)
	{
		if (arcadesList[index].isEmpty != 1 && arcadesList[index].idPlayroom == roomId)
		{
			counter++;
		}
	}

	if (counter > 4)
	{
		hasMoreThanFourArcades = 1;
	}
	return hasMoreThanFourArcades;
}
