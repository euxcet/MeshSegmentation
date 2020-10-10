#include "mesh.h"

Mesh::Mesh() {
    sp = new ShortestPath();
}

Mesh::~Mesh() {
    delete sp;
}

int Mesh::getFaceNum() {
    return faceNum;
}

float Mesh::getDistance(int p, int q) {
    assert(p < faceNum && q < faceNum);
    return sp -> distance[p][q];
}

float Mesh::angularDistance(float alpha) {
    return 1.0 - alpha;
}

Point3f Mesh::center(int p) {
    assert(p < faceNum);
    return (vertex[face[p].x] + vertex[face[p].y] + vertex[face[p].z]) / 3.0f;
}

float Mesh::geodesicDistance(Point3f p1, Point3f p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}

void Mesh::calculateDistance() {
    sp -> dijkstra(edge, faceNum);
}

void Mesh::load(const char* path) {
    ifstream fin(path);
    char t;
    string line;
    float x, y, z;
    int vx, vy, vz;
    while (fin >> t) {
        if (t == '#') {
            getline(fin, line);
        }
        else if (t == 'v') {
            fin >> x >> y >> z;
            vertex.push_back(Point3f(x, y, z));
            cout << x << " " << y << " " << z << endl;
        }
        else if (t == 'f') {
            face.push_back(Point3i(vx, vy, vz));
            cout << vx << " " << vy << " " << vz << endl;
        }
    }
    faceNum = face.size();
    fin.close();
}

bool Mesh::isNear(int p, int q) {
    assert(p < faceNum && q < faceNum);
    int sameVertex = 0;
    for(int i = 0; i < 3; i++) {
        bool isSame = false;
        for(int j = 0; j < 3; j++) {
            if (face[p][i] == face[q][j]) {
                isSame = true;
                break;
            }
        }
        if (isSame) {
            sameVertex ++;
        }
    }
    return sameVertex == 2;
}

float Mesh::dihedralAngle(int p, int q) {
    assert(isNear(p, q));
    Point3f lineX, lineY;
    Point3f planeX, planeY;
    bool sameX[3] = {false, false, false};
    bool sameY[3] = {false, false, false};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (face[p][i] == face[q][j]) {
                sameX[i] = true;
                sameY[j] = true;
                break;
            }
        }
    }
    for(int i = 0; i < 3; i++) {
        if (!sameX[i]) {
            planeX = vertex[face[p][i]];
            if (i == 0) {
                lineX = vertex[face[p][1]];
            }
            else {
                lineX = vertex[face[p][0]];
            }
            if (i == 2) {
                lineY = vertex[face[p][1]];
            }
            else {
                lineY = vertex[face[p][2]];
            }
        }
        if (!sameY[i]) {
            planeY = vertex[face[q][i]];
        }
    }
    Vector3f b0 = lineY - lineX;
    Vector3f b1 = planeX - lineX;
    Vector3f b2 = planeY - lineX;
    return (b0.cross(b1) * b0.cross(b2)) / (b0.cross(b1).length() * b0.cross(b2).length());
}

void Mesh::generateDual() {
    // optimize
    float delta = 0.5f;
    int adjNum = 0;
    float geodesicAvg = 0.0f;
    float angularAvg = 0.0f;
    
    for(int i = 0; i < faceNum; i++) {
        for(int j = i + 1; j < faceNum; j++) {
            if (isNear(i, j)) {
                geodesicAvg += geodesicDistance(center(i), center(j));
                angularAvg += angularDistance(dihedralAngle(i, j));
                adjNum ++;
            }
        }
    }

    geodesicAvg /= adjNum;
    angularAvg /= adjNum;

    for(int i = 0; i < faceNum; i++) {
        for(int j = 0; j < faceNum; j++) {
            if (i != j && isNear(i, j)) {
                float weight = delta * geodesicDistance(center(i), center(j)) / geodesicAvg +
                               (1 - delta) * angularDistance(dihedralAngle(i, j)) / angularAvg;
                edge[i][j] = weight;
            }
            else {
                edge[i][j] = MAXFLOAT;
            }
        }
    }
}