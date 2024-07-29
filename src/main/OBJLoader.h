#ifndef VOR_COURSEWORK_OBJLOADER_H
#define VOR_COURSEWORK_OBJLOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Vector3 {
    float x, y, z;
};

struct Vector2 {
    float u, v;
};

struct Face {
    int vertexIndex[3];
    int uvIndex[3];
    int normalIndex[3];
};

class OBJLoader {
public:
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
    std::vector<Face> faces;

    bool load(const char* filename);
};

#endif //VOR_COURSEWORK_OBJLOADER_H
