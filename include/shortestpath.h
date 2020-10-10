#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "defs.h"

class ShortestPath {
public:
    ShortestPath();
    void dijkstra(float edge[][MAXVERTEX], int n);

    float distance[MAXVERTEX][MAXVERTEX];
};

#endif