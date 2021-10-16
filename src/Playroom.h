/*
 * Playroom.h
 *
 *  Created on: 14 oct. 2021
 *      Author: Leandro
 */

#ifndef PLAYROOM_H_
#define PLAYROOM_H_
struct Playroom
{
	int id;
	char name[64];
	char address[64];
	int type;
	int isEmpty;
};
typedef struct Playroom Playroom;
int playroom_init(Playroom list[], int len);
int playroom_add(Playroom* pPlayroom);
int playroom_findAnEmptyPosition(Playroom list[], int listLen, int* pEmptyPosition);
int playroom_findById (Playroom list[], int listLen, int id, int* pFoundPosition);
int playroom_modify (Playroom* pPlayroom);
int playroom_deleteById(Playroom list[], int listLen, int id);
void playroom_printList(Playroom list[], int len, int printType);
int playroom_getId (int* pId);
#endif /* PLAYROOM_H_ */
