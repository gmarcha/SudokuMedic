#include "parser.h"

bool areNumsValid( string s, unsigned long max ) {

    s[max] = '\0';
    bool status = false;

    for (unsigned long i = 0; s[i] != '\0'; ++i) {
        for (unsigned long num = 0; num <= max; ++num) {
            if ((unsigned long)(s[i] - 48) == num) {
                status = true;
            }
        }
        if (status == false) {
            return false;
        }
        status = false;
    }
    return true;
}

gridPtr isGridValid( const string fileName ) {

    char buf[BUF_SIZE];

    FILE* fileStream = fopen(fileName, "r");
    if ( fileStream == NULL ) {
        return NULL;
    }
    gridPtr grid = malloc(sizeof(grid_t));
    if ( grid == NULL ) {
        return NULL;
    }

    if ( fgets( buf, BUF_SIZE, fileStream ) == NULL ) {
        return NULL;
    }
    grid->width = strlen(buf);
    if ( grid->width < 2 ) {
        return NULL;
    }
    if ( areNumsValid(buf, --grid->width) == false ) {
        return NULL;
    }
    grid->height = 1;
    grid->vector = malloc(sizeof(char) * GRID_SIZE);
    if ( grid->vector == NULL ) {
        return NULL;
    }
    strcpy(grid->vector, buf);

    unsigned long size = grid->width, offSet = 1;
    while ( fgets( buf, BUF_SIZE, fileStream ) != NULL ) {
        
        if ( grid->width != strlen(buf) - 1 || areNumsValid(buf, grid->width) == false ) {
            return NULL;
        }
        ++grid->height;
        if (size + grid->width > GRID_SIZE * offSet) {
            ++offSet;
            matrix tmp = realloc(grid->vector, sizeof(char) * GRID_SIZE * offSet);
            if (tmp == NULL) {
                return NULL;
            }
            free(grid->vector);
            grid->vector = tmp;
        }
        strcpy(grid->vector + size, buf);
        size += grid->width;
    }

    if ( grid->width != grid->height ) {
        return NULL;
    }

    return grid;
}
