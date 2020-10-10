#ifndef SPLITTER_H
#define SPLITTER_H

#include "defs.h"
#include "mesh.h"

class Splitter {
public:
    Splitter(Mesh* mesh);

    pair<Mesh*, Mesh*> binarySplit();

    void calculateProbability();

private:
    Mesh* mesh;
    float prob[MAXFACE];

};

#endif