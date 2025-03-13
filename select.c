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

    // Read the next argument after SELECT (either "ALL" or coordinates)
    scanf("%s", arg);

    // If "ALL" is selected, the entire image is set as the selection
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

        // Read the next three integers (should be the rest of the selection coordinates)
        res = scanf("%d%d%d", &tempy1, &tempx2, &tempy2);
        if (res != 3) { // If input is not valid, reset values and mark check as false
            check = 0;
            tempy1 = 0;
            tempx2 = 0;
            tempy2 = 0;
        }

        // Convert the first argument (arg) to an integer (first coordinate)
        if (strcmp(arg, "0") == 0) {
            tempx1 = 0;
        } else {
            tempx1 = atoi(arg);
            if (tempx1 == 0) // If conversion fails, set tempx1 to -1 (invalid case)
                tempx1 = -1;
        }

        // If no image is loaded, output an error
        if ((*size).error == -1) {
            printf("No image loaded\n");
        } else {
            int aux, ok = 1;

            // Check if the provided coordinates are valid
            if ((tempx1 < 0 || tempx2 < 0 || tempy1 < 0 || tempy2 < 0) &&
                check == 1) {
                printf("Invalid set of coordinates\n");
                ok = 0;
            }

            // Check if the coordinates are within image bounds
            if ((tempx1 > (*size).width || tempx2 > (*size).width ||
                 tempy1 > (*size).height || tempy2 > (*size).height) &&
                ok == 1 && check == 1) {
                printf("Invalid set of coordinates\n");
                ok = 0;
            }

            // Ensure that the selection is not a single line (non-zero area)
            if ((tempx1 == tempx2 || tempy1 == tempy2) && ok == 1 &&
                check == 1) {
                printf("Invalid set of coordinates\n");
                ok = 0;
            }

            // If input command was invalid, reset selection verification
            if (check == 0) {
                printf("Invalid command\n");
                ok = 0;
                (*size).verify = 0;
            } else {
                (*size).verify = 1;
            }

            // If all validations pass, store the selection in order
            if (ok == 1) {
                // Swap x1 and x2 if x1 is greater
                if (tempx1 > tempx2) {
                    aux = tempx1;
                    tempx1 = tempx2;
                    tempx2 = aux;
                }
                // Swap y1 and y2 if y1 is greater
                if (tempy1 > tempy2) {
                    aux = tempy1;
                    tempy1 = tempy2;
                    tempy2 = aux;
                }

                // Store the selected area
                (*size).x1 = tempx1;
                (*size).x2 = tempx2;
                (*size).y1 = tempy1;
                (*size).y2 = tempy2;

                // Confirm selection
                printf("Selected %d %d %d %d\n",
                       (*size).x1, (*size).y1, (*size).x2, (*size).y2);
            }
        }
    }
}
