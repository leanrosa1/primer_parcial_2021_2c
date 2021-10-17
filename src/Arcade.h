/*
 * Arcade.h
 *
 *  Created on: 14 oct. 2021
 *      Author: Leandro
 */

#ifndef ARCADE_H_
#define ARCADE_H_
#include "Playroom.h"
struct Arcade
{
	int id;
	char country[64];
	char game[64];
	int maxNumberOfCoins;
	int numberOfPlayers;
	int soundType;
	int idPlayroom;
	int isEmpty;
};
typedef struct Arcade Arcade;
int arcade_deleteById(Arcade list[], int listLen, int id);
void printArcadeWithRoomInfo (Arcade arcadesList[], int arcadeLen, Playroom playroomsList[], int roomLen);
int selectFieldToModify (int* selectedField);
int arcade_modifyGame (Arcade* pArcade);
int arcade_modifyNumberOfPlayers (Arcade* pArcade);
int arcade_findById (Arcade list[], int listLen, int id, int* pFoundPosition);
int arcade_findAnEmptyPosition(Arcade list[], int listLen, int* pEmptyPosition);
int arcade_add(Arcade* pArcade, Playroom list[], int len);
int arcade_init(Arcade list[], int len);
void arcade_printList(Arcade list[], int len);
void arcade_deleteByRoomId(Arcade arcadeList[], int arcadeListLen, int playroomId);
int arcade_validateIfIdExists (Arcade arcadeList[], int arcadeListLen, int arcadeId, int* arcadeIndex);
int validateIfPlayroomIdExists (Playroom list[], int len, int id);
#endif /* ARCADE_H_ */
