#include "splitter.h"

Splitter::Splitter(Mesh* mesh) : mesh(mesh) {

}

void Splitter::calculateProbability() {
    int n = mesh -> faceNum;
    float maxDistance = 0.0f;
    int repA = 0;
    int repB = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if (mesh -> getDistance(i, j) > maxDistance) {
                maxDistance = mesh -> getDistance(i, j);
                repA = i;
                repB = j;
            }
        }
    }
    int newRepA = -1;
    int newRepB = -1;
    while(true) {
        for(int i = 0; i < n; i++) {
            prob[i] = mesh -> getDistance(i, repB) / (mesh -> getDistance(i, repA) + mesh -> getDistance(i, repB))
        }
        float minValueA = MAXFLOAT;
        float minValueB = MAXFLOAT;
        for(int i = 0; i < n; i++) {
            float sumA = 0;
            float sumB = 0;
            for(int j = 0; j < n; j++) {
                sumA += prob[j] * mesh -> getDistance(i, j)
                sumB += (1 - prob[j]) * mesh -> getDistance(i, j)
            }
            if (sumA < minValueA) {
                minValueA = sumA;
                newRepA = i;
            }
            if (sumB < minValueB) {
                minValueB = sumB;
                newRepB = i;
            }
        }
        if (newRepA != repA || newRepB != repB) {
            newRepA = repA;
            newRepB = repB;
        }
        else {
            break;
        }
    }
}

pair<Mesh*, Mesh*> Splitter::binarySplit() {
    // stop condition
    mesh -> generateDual();
    mesh -> calculateDistance();
    calculateProbability();
    
}