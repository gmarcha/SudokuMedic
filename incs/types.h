#ifndef TYPES_H
# define TYPES_H

typedef char* string;
typedef char* matrix;

typedef struct coord_s {
    unsigned long x;
    unsigned long y;
} coord_t;

typedef struct node_s {
    struct node_s* next;
    coord_t coord;
} node_t;

typedef node_t* nodePtr;

typedef struct grid_s {
    matrix vector;
    matrix hints;
    nodePtr positionList;
    unsigned long width;
    unsigned long height; 
} grid_t;

typedef grid_t* gridPtr;

#endif // TYPES_H
