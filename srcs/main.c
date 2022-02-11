#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "parser.h"
#include "utils.h"

bool isMissingLine( unsigned long k, gridPtr grid, unsigned long i ) {

    for (unsigned long j = 0; j < grid->width; ++j) {
        if ((unsigned long)grid->vector[i * grid->width + j] == k + 48) {
            return false;
        }
    }
    return true;
}

bool isMissingColumn( unsigned long k, gridPtr grid, unsigned long j ) {

    for (unsigned long i = 0; i < grid->width; ++i) {
        if ((unsigned long)grid->vector[i * grid->width + j] == k + 48) {
            return false;
        }
    }
    return true;
}

bool isMissingBlock( unsigned long k, gridPtr grid, unsigned long i, unsigned long j ) {

    unsigned long _i = i - i % (unsigned long)sqrt(grid->width), _j = j - j % (unsigned long)sqrt(grid->width);
    for (i = _i; i < _i + (unsigned long)sqrt(grid->width); ++i) {
        for (j = _j; j < _j + (unsigned long)sqrt(grid->width); ++j) {
            if ((unsigned long)grid->vector[i * grid->width + j] == k + 48) {
                return false;
            }
        }
    }
    return true;
}

unsigned long countPossibleLine( gridPtr grid, unsigned long i ) {

    unsigned long count = 0;
    for (unsigned long j = 0; j < grid->width; ++j) {
        if (grid->vector[i * grid->width + j] != '0') {
            ++count;
        }
    }
    return count;
}

unsigned long countPossibleColumn( gridPtr grid, unsigned long j ) {

    unsigned long count = 0;
    for (unsigned long i = 0; i < grid->width; ++i) {
        if (grid->vector[i * grid->width + j] != '0') {
            ++count;
        }
    }
    return count;
}

unsigned long countPossibleBlock( gridPtr grid, unsigned long i, unsigned long j ) {

    unsigned long count = 0, _i = i - i % (unsigned long)sqrt(grid->width), _j = j - j % (unsigned long)sqrt(grid->width);
    for (i = _i; i < _i + (unsigned long)sqrt(grid->width); ++i) {
        for (j = _j; j < _j + (unsigned long)sqrt(grid->width); ++j) {
            if (grid->vector[i * grid->width + j] != '0') {
                ++count;
            }
        }
    }
    return count;
}

nodePtr getHints( gridPtr grid ) {

    grid->hints = malloc(sizeof(char) * grid->width * grid->width);
    if (grid->hints == NULL) {
        return NULL;
    }

    for (unsigned long i = 0; i < grid->width; ++i) {
        for (unsigned long j = 0; j < grid->width; ++j) {

            if ( grid->vector[i * grid->width + j] != '0' ) {
                grid->hints[i * grid->width + j] = '0';
            } else {

                unsigned long possibilites = grid->width, tmp = grid->width;;
                if (
                    ( tmp = countPossibleLine(grid, i) ) < possibilites ||
                    ( tmp = countPossibleColumn(grid, j) ) < possibilites ||
                    ( tmp = countPossibleBlock(grid, i, j) ) < possibilites
                ) {
                    possibilites = tmp;
                }
                grid->hints[i * grid->width + j] = possibilites + 48;
            }
        }
    }

    nodePtr tmp, node = NULL;

    for (unsigned long k = grid->width; k >= 1; --k) {

        for (unsigned long i = 0; i < grid->width; ++i) {
            for (unsigned long j = 0; j < grid->width; ++j) {

                if ((unsigned long)grid->hints[i * grid->width + j] == k + 48) {

                    tmp = malloc(sizeof(node_t));
                    if (tmp == NULL) {
                        return NULL;
                    }
                    tmp->coord.x = j;
                    tmp->coord.y = i;
                    tmp->next = node;
                    node = tmp;
                }
            }
        }
    }

    return node;
}

bool solveGrid( gridPtr grid ) {

    nodePtr position = getHints(grid);

    if (position == NULL) {
        return true;
    }

    unsigned long i = position->coord.y, j = position->coord.x;

    for (unsigned long k = 1; k <= grid->width; ++k) {

        if (isMissingLine(k, grid, i) == true && isMissingColumn(k, grid, j) == true && isMissingBlock(k, grid, i, j) == true) {
            grid->vector[i * grid->width + j] = k + 48;

            // printGrid(grid);

            if ( solveGrid (grid /*, position->next */) ) {
                return true;
            }
        }
    }
    grid->vector[i * grid->width + j] = '0';

    return false;
}

int main( int ac, char* av[] ) {

    gridPtr grid;

    if ( ac != 2 ) {
        printErr( ac < 2 ? "missing argument" : "too much arguments" );
        return EXIT_FAILURE;
    }
    if ( ( grid = isGridValid(av[1]) ) == NULL ) {
        printErr( "grid is invalid" );
        return EXIT_FAILURE;
    }
    if ( solveGrid(grid) == false ) {
        return EXIT_FAILURE;
    }
    printGrid(grid);
    return EXIT_SUCCESS;
}