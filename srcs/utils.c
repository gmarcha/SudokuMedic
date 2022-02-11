#include "utils.h"

void printErr( const string errMsg ) { fprintf(stderr, "%s: invalid input: %s\n", PROGRAM_NAME, errMsg); }

void printGrid( gridPtr grid ) {

    for (unsigned long i = 0; i < grid->width; ++i) {
        if (i % (unsigned long)sqrt(grid->width) == 0) {
            for (unsigned long i = 0; i < grid->width + (unsigned long)sqrt(grid->width) + 1; ++i) {
                printf("-");
            }
            printf("\n");
        }
        for (unsigned long j = 0; j < grid->width; ++j) {
            if (j % (unsigned long)sqrt(grid->width) == 0) {
                printf("|");
            }
            printf("%c", grid->vector[i * grid->width + j]);
        }
        printf("|\n");
    }
    for (unsigned long i = 0; i < grid->width + (unsigned long)sqrt(grid->width) + 1; ++i) {
        printf("-");
    }
    printf("\n");
}