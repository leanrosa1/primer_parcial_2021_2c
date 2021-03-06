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
	int numberOfPlayrooms = 0;
	int numberOfArcades = 0;
	int arcadesToDelete;

	playroom_init(playroomsList, PLAYROOMS_LEN);
	arcade_init(arcadesList, ARCADES_LEN);

	//forced adds [IGNORE]
	for (int i = 0; i < 6; i++)
	{
		playroom_forceAdd(&playroomsList[i]);
		numberOfPlayrooms++;
	}

	for (int k = 0; k < 9; k++)
	{
		arcade_forceAdd(&arcadesList[k]);
		numberOfArcades++;
	}
	arcade_forceAdd2(&arcadesList[9]);
	arcade_forceAdd2(&arcadesList[10]);
	arcade_forceAdd3(&arcadesList[11]);
	arcade_forceAdd3(&arcadesList[12]);
	numberOfArcades += 4;

	//end of forced adds

	do
	{
		menu_printMainMenu();
		if (menu_selectAnOption(&selectedOption, 1, 10) == 1)
		{
			switch (selectedOption)
			{
				case 1:
					if (menu_optionOne(playroomsList, PLAYROOMS_LEN) == 1)
						numberOfPlayrooms++;
					break;
				case 2:
					if (menu_optionTwo(playroomsList, PLAYROOMS_LEN, arcadesList, ARCADES_LEN, numberOfPlayrooms, &arcadesToDelete) == 1)
					{
						numberOfPlayrooms--;
						numberOfArcades = numberOfArcades - arcadesToDelete;
						printf("\nSal?n eliminado correctamente");
					}
					break;
				case 3:
					menu_optionThree(playroomsList, PLAYROOMS_LEN, numberOfPlayrooms);
					break;
				case 4:
					if (menu_optionFour(arcadesList, ARCADES_LEN, playroomsList, PLAYROOMS_LEN, numberOfPlayrooms) == 1)
						numberOfArcades++;
					break;
				case 5:
					menu_optionFive(arcadesList, ARCADES_LEN, numberOfArcades);
					break;
				case 6:
					if (menu_optionSix(arcadesList, ARCADES_LEN, playroomsList, PLAYROOMS_LEN, numberOfArcades) == 1)
					{
						printf("\nArcade eliminado exitosamente");
						numberOfArcades--;
					}
					break;
				case 7:
					menu_optionSeven(arcadesList, ARCADES_LEN, numberOfArcades);
					break;
				case 8:
					menu_optionEight(arcadesList, ARCADES_LEN, numberOfArcades);
					break;
				case 9:
					menu_optionNine(playroomsList, PLAYROOMS_LEN, arcadesList, ARCADES_LEN, numberOfArcades, numberOfPlayrooms);
					break;
				case 10:
					printf("\nFinalizando programa...");
			}
		}
		else
		{
			printf("\nError al elegir la opci?n. Finalizando programa...");
			exit(0);
		}
	} while (selectedOption != 10);
	return EXIT_SUCCESS;
}
