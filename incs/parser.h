#ifndef PARSER_H
# define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "types.h"

bool areNumsValid( string s, unsigned long max );
// Check if string s contains only digits less than or equal to max.

gridPtr isGridValid( const string fileName );
// Parse the file which contains the grid, and check its validity.

#endif // PARSER_H
