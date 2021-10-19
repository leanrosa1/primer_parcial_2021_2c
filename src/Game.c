/*
 * Games.c
 *
 *  Created on: 16 oct. 2021
 *      Author: Leandro
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arcade.h"
#include "Game.h"

#define GAMES_LEN 63

//private prototypes
static int isThisGameInList (char gameName[], Game gameList[], int listLen);
static void initGameList (Game gameList[], int listLen);

/**
 * \brief: Get a list of unrepeated games that appears in an arcades list
 *
 * \param arcadeList: arcades array
 * \param listLen: length of arcades array
 * \param gameList: char pointer to write the list of games
 * \return 1 if OK // -1 if Error
 */
int game_getList (Arcade arcadeList[], int listLen, Game gameList[])
{
	int status = -1;
	int index;
	int gameListIndex = 0;

	if (arcadeList != NULL && gameList != NULL && listLen > 0)
	{
		initGameList(gameList, listLen);
		for (index = 0; index < listLen; index++)
		{
			if (arcadeList[index].isEmpty != 1)
			{
				if (isThisGameInList(arcadeList[index].game, gameList, listLen) == -1)
				{
					strncpy(gameList[gameListIndex].name, arcadeList[index].game, GAMES_LEN);
					gameList[gameListIndex].isEmpty = -1;
					gameListIndex++;
				}
			}
		}
		status = 1;
	}
	return status;
}

/**
 * \brief: Print every active game in games list
 *
 * \param gameList: games array
 * \param listLen: length of games array
 * \return 1 if OK // -1 if Error
 */
int game_printList (Game gameList[], int listLen)
{
	int status = -1;
	int index;

	if (gameList != NULL && listLen > 0)
	{
		if (gameList[0].isEmpty != 1)
		{
			status = 1;
			for (index = 0; index < listLen; index++)
			{
				if (gameList[index].isEmpty != 1)
				{
					printf("\n-------------------------------------------");
					printf("\nNOMBRE DE JUEGO: %s", gameList[index].name);
				}
				else
					break;
			}
		}
	}
	return status;
}

/**
 * \brief: Put every game's isEmpty flag in 1

 * \param gameList: a Game array
 * \param listLen: length of the array
 * \return 1 if OK // -1 if Error
 */
static void initGameList (Game gameList[], int listLen)
{
	int index;

	for (index = 0; index < listLen; index++)
	{
		gameList[index].isEmpty = 1;
	}
}

/**
 * \brief: Check if a given game exists in a given games lists

 * \param gameName: name of the game to search by
 * \param gameList: a Game array
 * \param listLen: length of the array
 * \return 1 if exists // -1 if not exists
 */
static int isThisGameInList (char gameName[], Game gameList[], int listLen)
{
	int wasFound = -1;
	int index;

	for (index = 0; index < listLen; index++)
	{
		if (gameList[index].isEmpty != 1)
		{
			if (strncmp(gameName, gameList[index].name, GAMES_LEN) == 0)
			{
				wasFound = 1;
				break;
			}
		}
	}
	return wasFound;
}
