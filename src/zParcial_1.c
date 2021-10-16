/*
 ============================================================================
 Name        : Parcial_1.c
 Author      : Leandro Rosa
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Playroom.h"
#include "Arcade.h"
#include "Game.h"
#include "menu.h"

#define PLAYROOMS_LEN 100
#define ARCADES_LEN 1000

int main(void) {
	setbuf(stdout, NULL);

	Playroom playroomsList[PLAYROOMS_LEN];
	Arcade arcadesList[ARCADES_LEN];
	int selectedOption;
	int playroomsQuantity = 0;
	int arcadesQuantity = 0;

	playroom_init(playroomsList, PLAYROOMS_LEN);
	arcade_init(arcadesList, ARCADES_LEN);

	do
	{
		menu_printMainMenu();
		if (menu_selectAnOption(&selectedOption, 1, 10) == 1)
		{
			switch (selectedOption)
			{
				case 1:
					if (menu_optionOne(playroomsList, PLAYROOMS_LEN) == 1)
						playroomsQuantity++;
					break;
				case 2:
					if (menu_optionTwo(playroomsList, PLAYROOMS_LEN, arcadesList, ARCADES_LEN, playroomsQuantity) == 1)
					{
						playroomsQuantity--;
						printf("\nSalón eliminado correctamente");
					}
					break;
				case 3:
					menu_optionThree(playroomsList, PLAYROOMS_LEN, playroomsQuantity);
					break;
				case 4:
					if (menu_optionFour(arcadesList, ARCADES_LEN, playroomsList, PLAYROOMS_LEN, playroomsQuantity) == 1)
						arcadesQuantity++;
					break;
				case 5:
					menu_optionFive(arcadesList, ARCADES_LEN, arcadesQuantity);
					break;
				case 6:
					if (menu_optionSix(arcadesList, ARCADES_LEN, playroomsList, PLAYROOMS_LEN, arcadesQuantity) == 1)
					{
						printf("\nArcade eliminado exitosamente");
						arcadesQuantity--;
					}
					break;
				case 7:
					menu_optionSeven(arcadesList, ARCADES_LEN, arcadesQuantity);
					break;
				case 8:
					menu_optionEight(arcadesList, ARCADES_LEN, arcadesQuantity);
					break;
				case 9:
					//mostar submenu de informes
					break;
				case 10:
					printf("\nFinalizando programa...");
			}
		}
		else
		{
			printf("\nError al elegir la opción. Finalizando programa...");
			exit(0);
		}
	} while (selectedOption != 10);
	return EXIT_SUCCESS;
}
