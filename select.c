#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

void SELECT(details *size)
{
	char arg[10];
	int res, check = 1;
	//we see what is to be read after SELECT
	scanf("%s", arg);
	if (strcmp(arg, "ALL") == 0) {
		if ((*size).error == -1) {
			printf("No image loaded\n");
		} else {
			printf("Selected ALL\n");
			(*size).x1 = 0;
			(*size).x2 = (*size).width;
			(*size).y1 = 0;
			(*size).y2 = (*size).height;
		}
	} else {
		int tempx1, tempx2, tempy1, tempy2;
		res = scanf("%d%d%d", &tempy1, &tempx2, &tempy2);
		if (res != 3) {
			check = 0;
			tempy1 = 0;
			tempx2 = 0;
			tempy2 = 0;
		}
		//turn the string into a number and check if it is a number
		if (strcmp(arg, "0") == 0) {
			tempx1 = 0;
		} else {
			tempx1 = atoi(arg);
			if (tempx1 == 0)
				tempx1 = -1;
		}
		if ((*size).error == -1) {
			printf("No image loaded\n");
		} else {
			int aux, ok = 1;
			//check the correctness of the coordinates
			if ((tempx1 < 0 || tempx2 < 0 || tempy1 < 0 || tempy2 < 0) &&
				check == 1) {
				printf("Invalid set of coordinates\n");
				ok = 0;
			}
			if ((tempx1 > (*size).width || tempx2 > (*size).width ||
				 tempy1 > (*size).height || tempy2 > (*size).height) &&
				 ok == 1 && check == 1) {
				printf("Invalid set of coordinates\n");
				ok = 0;
			}
			if ((tempx1 == tempx2 || tempy1 == tempy2) && ok == 1 &&
				check == 1) {
				printf("Invalid set of coordinates\n");
				ok = 0;
			}
			if (check == 0) {
				printf("Invalid command\n");
				ok = 0;
				(*size).verify = 0;
			} else {
				(*size).verify = 1;
			}
			if (ok == 1) {
				if (tempx1 > tempx2) {
					aux = tempx1;
					tempx1 = tempx2;
					tempx2 = aux;
				}
				if (tempy1 > tempy2) {
					aux = tempy1;
					tempy1 = tempy2;
					tempy2 = aux;
				}
				(*size).x1 = tempx1;
				(*size).x2 = tempx2;
				(*size).y1 = tempy1;
				(*size).y2 = tempy2;
				printf("Selected %d %d %d %d\n",
					   (*size).x1, (*size).y1, (*size).x2, (*size).y2);
			}
		}
	}
}