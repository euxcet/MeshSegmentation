#ifndef MESH_H
#define MESH_H

#include "defs.h"
#include "point.h"
#include "shortestpath.h"


class Mesh {
public:
    Mesh();
    ~Mesh();

    void load(const char* path);

    bool isNear(int p, int q);

    int getFaceNum();
    
    float getDistance(int p, int q);

    float dihedralAngle(int p, int q);

    void generateDual();

    float angularDistance(float alpha);

    float geodesicDistance(Point3f p1, Point3f p2);

    void calculateDistance();

    Point3f center(int p);

private:
    vector<Point3f> vertex;
    vector<Point3i> face;

    int faceNum;
    ShortestPath *sp;
    float edge[MAXVERTEX][MAXVERTEX];
    float distance[MAXVERTEX][MAXVERTEX];
};

#endif