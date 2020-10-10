#include "mesh.h"

int main(int argc, char* argv[]) {
    Mesh* mesh = new Mesh();
    mesh -> load("models/cube.obj");
    delete mesh;
}