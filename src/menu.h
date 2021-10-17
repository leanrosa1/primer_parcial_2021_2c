/*
 * menu.h
 *
 *  Created on: 6 oct. 2021
 *      Author: Leandro
 */

#ifndef MENU_H_
#define MENU_H_
void menu_printMainMenu (void);
int menu_selectAnOption (int* selectedOption, int minValue, int maxValue);
int menu_optionOne (Playroom playroomList[], int listLen);
int menu_optionTwo (Playroom playroomList[], int playroomListLen, Arcade arcadeList[], int arcadeListLen, int playroomsQuantity);
void menu_optionThree (Playroom playroomList[], int playroomListLen, int playroomsQuantity);
int menu_optionFour (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int playroomsQuantity);
void menu_optionFive (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity);
int menu_optionSix (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int arcadesQuantity);
void menu_optionSeven (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity);
void menu_optionEight (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity);
int  menu_optionNine (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
int menu_optionA (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
void menu_optionB (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades);
void menu_optionC (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfPlayrooms);
void menu_optionD (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
void menu_optionE (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
void menu_optionF (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
void menu_optionG (Arcade arcadesList[], int arcadesListLen, int numberOfArcades);
#endif /* MENU_H_ */
