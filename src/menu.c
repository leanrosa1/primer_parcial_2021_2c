/*
 * menu.c
 *
 *  Created on: 6 oct. 2021
 *      Author: Leandro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "Playroom.h"
#include "Arcade.h"
#include "Game.h"

//private prototypes
static void printfModifyArcadeMenu (void);

void menu_printMainMenu (void) //CUIDADO OPCIONES
{
	printf("\n");
	printf("\n--------MENU--------");
	printf("\n1. ALTA DE SALON");
	printf("\n2. ELIMINAR SALON");
	printf("\n3. IMPRIMIR SALONES");
	printf("\n4. INCORPORAR ARCADE");
	printf("\n5. MODIFICAR ARCADE");
	printf("\n6. ELIMINAR ARCADE");
	printf("\n7. IMPRIMIR ARCADES");
	printf("\n8. IMPRIMIR JUEGOS");
	printf("\n9. INFORMES");
	printf("\n10. SALIR");
	printf("\n--------------------");
}

int menu_selectAnOption (int* selectedOption, int minValue, int maxValue)
{
	int status = -1;
	int auxiliarSelectedOption;
	if (input_getInt(minValue, maxValue, 2, "Seleccione una opción", &auxiliarSelectedOption, "Error") == 1)
	{
		status = 1;
		*selectedOption = auxiliarSelectedOption;
	}
	return status;
}

int menu_optionOne (Playroom playroomList[], int listLen)
{
	int status = -1;
	int emptyPosition;

	if (playroomList != NULL && listLen > 0)
	{
		if (playroom_findAnEmptyPosition(playroomList, listLen, &emptyPosition) == 1)
		{
			if (playroom_add(&playroomList[emptyPosition]) == 1)
			{
				status = 1;
			}
		}
	}
	return status;
}

int menu_optionTwo (Playroom playroomList[], int playroomListLen, Arcade arcadeList[], int arcadeListLen, int playroomsQuantity)
{
	int status = -1;
	int id;

	if (playroomList != NULL && playroomListLen > 0)
	{
		if (playroomsQuantity > 0)
		{
			playroom_printList(playroomList, playroomListLen, 0);
			if (playroom_getId(&id) == 1)
			{
				if (playroom_deleteById(playroomList, playroomListLen, id) == 1)
				{
					arcade_deleteByRoomId(arcadeList, arcadeListLen, id);
					status = 1;
				}
			}
		}
		else
			printf("\nNo hay salones para eliminar");
	}
	return status;
}

void menu_optionThree (Playroom playroomList[], int playroomListLen, int playroomsQuantity)
{
	if (playroomList != NULL && playroomListLen > 0)
	{
		if (playroomsQuantity > 0)
		{
			playroom_printList(playroomList, playroomListLen, 1);
		}
		else
			printf("\nNo hay salones para listar");
	}
}

int menu_optionFour (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int playroomsQuantity)
{
	int status = -1;
	int emptyPosition;

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (playroomsQuantity > 0)
		{
			if (arcade_findAnEmptyPosition(arcadeList, arcadeListLen, &emptyPosition) == 1)
			{
				if (arcade_add(&arcadeList[emptyPosition], playroomList, playroomListLen) == 1)
				{
					status = 1;
				}
			}
		}
		else
			printf("\nSe necesita al menos un salón para cargar un arcade");
	}
	return status;
}

void menu_optionFive (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity)
{
	int selectedOption;
	int id;
	int arcadeIndex;
	int gameListLen = arcadeListLen;
	Game gameList[gameListLen];

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (arcadesQuantity > 0)
		{
			arcade_printList(arcadeList, arcadeListLen);
			if (input_getInt(1, 9999, 2, "\n->Ingrese el id del arcade que desea modificar", &id, "Error") == 1)
			{
				if (arcade_validateIfIdExists(arcadeList, arcadeListLen, id, &arcadeIndex) == 1)
				{
					printfModifyArcadeMenu();
					if (input_getInt(1, 2, 2, "\n->Elija una opción", &selectedOption, "Error") == 1)
					{
						if (selectedOption == 1)
						{
							arcade_modifyNumberOfPlayers(&arcadeList[arcadeIndex]);
						}
						else
						{
							if (game_getList(arcadeList, arcadeListLen, gameList) == 1)
							{
								printf("\nENtre");
								game_printList(gameList, gameListLen);
								arcade_modifyGame(&arcadeList[arcadeIndex]);
							}
						}
					}
				}
				else
					printf("\nEl arcade con id indicado no existe");
			}
		}
		else
			printf("\nNo hay arcades para modificar");
	}
}

int menu_optionSix (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int arcadesQuantity)
{
	int status = -1;
	int id;
	int arcadeIndex;
	int selectedOption;

	if (arcadeList != NULL && arcadeListLen > 0 && playroomList != NULL && playroomListLen > 0)
	{
		if (arcadesQuantity > 0)
		{
			printArcadeWithRoomInfo(arcadeList, arcadeListLen, playroomList, playroomListLen);
			if (input_getInt(1, 9999, 2, "\n->Ingrese el id del arcade que desea eliminar", &id, "Error") == 1)
			{
				if (arcade_validateIfIdExists(arcadeList, arcadeListLen, id, &arcadeIndex) == 1)
				{
					printf("\nID: %d", arcadeList[arcadeIndex].id);
					printf("\nPAIS: %s", arcadeList[arcadeIndex].country);
					printf("\nJUEGO: %s", arcadeList[arcadeIndex].game);
					printf("\nMAXIMO NUMERO DE FICHAS: %d", arcadeList[arcadeIndex].maxNumberOfCoins);
					printf("\nNUMERO DE JUGADORES: %d", arcadeList[arcadeIndex].numberOfPlayers);
					printf("\nSONIDO: %d", arcadeList[arcadeIndex].soundType);
					printf("\nPERTENECE A SALON ID %d", arcadeList[arcadeIndex].idPlayroom);
					if (input_getInt(1, 2, 2, "\n->¿Seguro deseas eliminar este arcade?\n1.Si\n2.No", &selectedOption, "Error") == 1)
					{
						if (selectedOption == 1)
						{
							if (arcade_deleteById(arcadeList, arcadeListLen, id) == 1)
							status = 1;
						}
						else
							printf("\nEliminacion cancelada");
					}
				}
				else
					printf("\nEl arcade con id indicado no existe");
			}
		}
		else
			printf("\nNo hay arcades para eliminar");
	}
	return status;
}

void menu_optionSeven (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity)
{
	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (arcadesQuantity > 0)
		{
			arcade_printList(arcadeList, arcadeListLen);
		}
		else
			printf("\nNo hay arcades para listar");
	}
}

void menu_optionEight (Arcade arcadeList[], int arcadeListLen, int arcadesQuantity)
{
	int gameListLen = arcadeListLen;
	Game gameList[gameListLen];

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (arcadesQuantity > 0)
		{
			if (game_getList(arcadeList, arcadeListLen, gameList) == 1)
			{
				game_printList(gameList, gameListLen);
			}
		}
		else
			printf("\nNo hay juegos por listar porque no hay arcades cargados en el sistema");
	}
}

static void printfModifyArcadeMenu (void)
{
	printf("\n----------------------------------------");
	printf("\n1. Modificar cantidad de jugadores");
	printf("\n2. Modificar juego del arcade");
	printf("\n----------------------------------------");
}



