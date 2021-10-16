/*
 * Games.h
 *
 *  Created on: 16 oct. 2021
 *      Author: Leandro
 */

#ifndef GAME_H_
#define GAME_H_

struct Game
{
	char name[63];
	int isEmpty;
};
typedef struct Game Game;

int game_getList (Arcade arcadeList[], int listLen, Game gameList[]);
int game_printList (Game gameList[], int listLen);
#endif /* GAME_H_ */
