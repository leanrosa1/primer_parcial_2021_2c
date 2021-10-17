/*
 * report.h
 *
 *  Created on: 17 oct. 2021
 *      Author: Leandro
 */

#ifndef REPORT_H_
#define REPORT_H_
int report_playroomsOverFourArcades (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen);
int report_arcadesOverTwoPlayers (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen);
int report_playroomById (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int playroomId);
int report_arcadesByPlayroomId (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int playroomId);
int report_maxNumberOfArcadesPlayroom (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen);
int report_maxAmountOfPlayroom (Arcade arcadesList[], int arcadesListLen, int playroomId, float coinPrice);
int report_howManyArcadesHasThisGame (Arcade arcadesList[], int arcadesListLen, char gameName[]);
#endif /* REPORT_H_ */
