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
#include "report.h"

#define GAME_NAME_LEN 63

//private prototypes
static void printfModifyArcadeMenu (void);
static void printReportsMenu (void);
static int menu_subOption1 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
static void menu_subOption2 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades);
static void menu_subOption3 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfPlayrooms);
static void menu_subOption4 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
static void menu_subOption5 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
static void menu_subOption6 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms);
static void menu_subOption7 (Arcade arcadesList[], int arcadesListLen, int numberOfArcades);

/**
 * \brief: Print software main menu
 */
void menu_printMainMenu (void)
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

/**
 * \brief: Ask user to select an integer option within a given range
 *
 * \param selectedOption: int pointer to write user's input
 * \param minValue: minimum allowed value
 * \param maxValue: maximum allowed value
 * \return 1 if OK // -1 if Error
 */
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

/**
 * \brief: Find an empty position in a given playrooms array and ask user to fill all playroom struct fields.
 *
 * \param playroomList: a playrooms array
 * \param listLen: length of playrooms array
 * \return 1 if OK // -1 if Error
 */
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

/**
 * \brief: Print a list of active playrooms and ask user to enter an ID
 * 			Find the playroom with the given ID (if exists) and delete it
 *
 * \param playroomList: a playrooms array
 * \param playroomListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
int menu_optionTwo (Playroom playroomList[], int playroomListLen, Arcade arcadeList[], int arcadeListLen, int numberOfPlayrooms, int* arcadesToDelete)
{
	int status = -1;
	int id;
	int numberOfArcadesToDelete;

	if (playroomList != NULL && playroomListLen > 0)
	{
		if (numberOfPlayrooms > 0)
		{
			playroom_printList(playroomList, playroomListLen, 0);
			if (playroom_getId(&id) == 1)
			{
				numberOfArcadesToDelete = report_getNumberOfArcadesByPlayroomId(arcadeList, arcadeListLen, id);
				if (playroom_deleteById(playroomList, playroomListLen, id) == 1)
				{
					*arcadesToDelete = numberOfArcadesToDelete;
					arcade_deleteByRoomId(arcadeList, arcadeListLen, id);
					status = 1;
				}
				else
					printf("\nEl salón con id indicado no fue encontrado");
			}
		}
		else
			printf("\nNo hay salones para eliminar");
	}
	return status;
}

/**
 * \brief: Print a list of active playrooms
 *
 * \param playroomList: a playrooms array
 * \param playroomListLen: length of playrooms array
 * \param numberOfPlayrooms: number of active playrooms
 */
void menu_optionThree (Playroom playroomList[], int playroomListLen, int numberOfPlayrooms)
{
	if (playroomList != NULL && playroomListLen > 0)
	{
		if (numberOfPlayrooms > 0)
		{
			playroom_printList(playroomList, playroomListLen, 1);
		}
		else
			printf("\nNo hay salones para listar");
	}
}

/**
 * \brief: Find an empty position in a given arcades array and ask user to fill all arcade struct fields.
 *
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param playroomList: a playrooms array
 * \param playroomListLen: length of playrooms array
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
int menu_optionFour (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int numberOfPlayrooms)
{
	int status = -1;
	int emptyPosition;

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (numberOfPlayrooms > 0)
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

/**
 * \brief: Allow user to modify number of players or game name of an specific arcade
 *
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \return 1 if OK // -1 if Error
 */
void menu_optionFive (Arcade arcadeList[], int arcadeListLen, int numberOfArcades)
{
	int selectedOption;
	int id;
	int arcadeIndex;
	int gameListLen = arcadeListLen;
	Game gameList[gameListLen];

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (numberOfArcades > 0)
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

/**
 * \brief: Print a list of active arcades and ask user to enter an ID
 * 			Find the arcade with the given ID (if exists) and delete it
 *
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param playroomList: a playrooms array
 * \param playroomListLen: length of playrooms array
 * \param numberOfArcades: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
int menu_optionSix (Arcade arcadeList[], int arcadeListLen, Playroom playroomList[], int playroomListLen, int numberOfArcades)
{
	int status = -1;
	int id;
	int arcadeIndex;
	int selectedOption;

	if (arcadeList != NULL && arcadeListLen > 0 && playroomList != NULL && playroomListLen > 0)
	{
		if (numberOfArcades > 0)
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

/**
 * \brief: Print a list of active arcades
 *
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 */
void menu_optionSeven (Arcade arcadeList[], int arcadeListLen, int numberOfArcades)
{
	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (numberOfArcades > 0)
		{
			arcade_printList(arcadeList, arcadeListLen);
		}
		else
			printf("\nNo hay arcades para listar");
	}
}

/**
 * \brief: Print an unrepetead list of games
 *
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 */
void menu_optionEight (Arcade arcadeList[], int arcadeListLen, int numberOfArcades)
{
	int gameListLen = arcadeListLen;
	Game gameList[gameListLen];

	if (arcadeList != NULL && arcadeListLen > 0)
	{
		if (numberOfArcades > 0)
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

/**
 * \brief: Ask user to select a report
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
int menu_optionNine (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms)
{
	int selectedOption;

	printReportsMenu();
	if (menu_selectAnOption(&selectedOption, 1, 7) == 1)
	{
		switch (selectedOption)
		{
			case 1:
				menu_subOption1(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfArcades, numberOfPlayrooms);
				break;
			case 2:
				menu_subOption2(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfArcades);
				break;
			case 3:
				menu_subOption3(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfPlayrooms);
				break;
			case 4:
				menu_subOption4(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfArcades, numberOfPlayrooms);
				break;
			case 5:
				menu_subOption5(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfArcades, numberOfPlayrooms);
				break;
			case 6:
				menu_subOption6(playroomsList, playroomsListLen, arcadesList, arcadesListLen, numberOfArcades, numberOfPlayrooms);
				break;
			case 7:
				menu_subOption7(arcadesList, arcadesListLen, numberOfArcades);
				break;
		}
	}
	return 0;
}

/**
 * \brief: Report playrooms which have more than four arcades
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static int menu_subOption1 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms)
{
	if (numberOfPlayrooms > 0 && numberOfArcades > 3)
	{
		if (report_playroomsOverFourArcades(playroomsList, playroomsListLen, arcadesList, arcadesListLen) != 1)
		{
			printf("\nNo se pudo procesar el informe");
		}
	}
	else
	{
		printf("\nNo hay suficientes salones o arcades para realizar el informe");
	}
	return 1;
}

/**
 * \brief: Report arcades which are for more than two players
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption2 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades)
{
	if (numberOfArcades > 0)
	{
		if (report_arcadesOverTwoPlayers(playroomsList, playroomsListLen, arcadesList, arcadesListLen) != 1)
		{
			printf("\nNo se pudo procesar el informe");
		}
	}
	else
		printf("\nDebe existir al menos un arcade para realizar el informe");
}

/**
 * \brief: Report information about an specific playroom
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption3 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfPlayrooms)
{
	int id;

	if (numberOfPlayrooms > 0)
	{
		playroom_printList(playroomsList, playroomsListLen, 1);
		if (playroom_getId(&id) == 1)
		{
			if (validateIfPlayroomIdExists(playroomsList, playroomsListLen, id) == 1)
			{
				if (report_playroomById(playroomsList, playroomsListLen, arcadesList, arcadesListLen, id) != 1)
				{
					printf("\nNo se pudo procesar el informe");
				}
			}
			else
				printf("\nEl salón con ID %d no existe", id);
		}
		else
			printf("\nError al ingresar el id");
	}
	else
		printf("\nDebe existir al menos un salon para realizar el informe");
}

/**
 * \brief: Report every arcade of an specific playroom
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption4 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms)
{
	int id;

	if (numberOfPlayrooms > 0 && numberOfArcades > 0)
	{
		playroom_printList(playroomsList, playroomsListLen, 1);
		if (playroom_getId(&id) == 1)
		{
			if (validateIfPlayroomIdExists(playroomsList, playroomsListLen, id) == 1)
			{
				if (report_arcadesByPlayroomId(playroomsList, playroomsListLen, arcadesList, arcadesListLen, id) != 1)
				{
					printf("\nNo se pudo procesar el informe");
				}
			}
			else
				printf("\nEl salón con ID %d no existe", id);
		}
		else
			printf("\nError al ingresar el id");
	}
	else
		printf("\nNo hay suficientes salones o arcades para realizar el informe");
}

/**
 * \brief: Report the playroom which has the biggest number of arcades
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption5 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms)
{
	if (numberOfPlayrooms > 0 && numberOfArcades > 0)
	{
		if (report_maxNumberOfArcadesPlayroom(playroomsList, playroomsListLen, arcadesList, arcadesListLen) != 1)
		{
			printf("\nNo se pudo procesar el informe");
		}
	}
	else
		printf("\nNo hay suficientes salones o arcades para realizar el informe");
}

/**
 * \brief: Report the maximum income possible of an specific playroom
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption6 (Playroom playroomsList[], int playroomsListLen, Arcade arcadesList[], int arcadesListLen, int numberOfArcades, int numberOfPlayrooms)
{
	int id;
	float coinPrice;

	if (numberOfPlayrooms > 0 && numberOfArcades > 0)
	{
		if (playroom_getId(&id) == 1)
		{
			if (validateIfPlayroomIdExists(playroomsList, playroomsListLen, id) == 1)
			{
				if (input_getFloat(1, 100, 2, "\n->Ingrese el precio de las fichas", &coinPrice, "Error") == 1)
				{
					if (report_maxAmountOfPlayroom(arcadesList, arcadesListLen, id, coinPrice) != 1)
					{
						printf("\nNo se pudo procesar el informe");
					}
				}
				else
					printf("\nError al ingresar el precio de las fichas");
			}
			else
				printf("\nEl salón con ID %d no existe", id);
		}
		else
			printf("\nError al ingresar el id");
	}
	else
		printf("\nNo hay suficientes salones o arcades para realizar el informe");
}

/**
 * \brief: Report how many arcades have an specific game
 *
 * \param playroomsList: a playrooms array
 * \param playroomsListLen: length of playrooms array
 * \param arcadeList: an arcades array
 * \param arcadeListLen: length of arcades array
 * \param numberOfArcades: number of active arcades
 * \param numberOfPlayrooms: number of active playrooms
 * \return 1 if OK // -1 if Error
 */
static void menu_subOption7 (Arcade arcadesList[], int arcadesListLen, int numberOfArcades)
{
	char gameName[GAME_NAME_LEN];

	if (numberOfArcades > 0)
	{
		if (input_getText(gameName, GAME_NAME_LEN, 2, "\n->Ingrese el nombre del juego", "Error") == 1)
		{
			if (report_howManyArcadesHasThisGame(arcadesList, arcadesListLen, gameName) != 1)
			{
				printf("\nNo se pudo procesar el informe");
			}
		}
		else
			printf("\nError al ingresar el nombre");
	}
	else
		printf("\nDebe existir al menos un arcade registrado para realizar el informe");
}

static void printReportsMenu (void)
{
	printf("\n---------------------INFORMAR---------------------");
	printf("\n1. Salones con más de 4 arcades");
	printf("\n2. Arcades para más de dos jugadores");
	printf("\n3. Informacion de un salon");
	printf("\n4. Arcades de un salon");
	printf("\n5. Salon con mayor cantidad de arcades");
	printf("\n6. Mayor recaudación posible de un salon");
	printf("\n7. Arcades que contienen un juego determinado");
	printf("\n--------------------------------------------------");
}

static void printfModifyArcadeMenu (void)
{
	printf("\n----------------------------------------");
	printf("\n1. Modificar cantidad de jugadores");
	printf("\n2. Modificar juego del arcade");
	printf("\n----------------------------------------");
}



