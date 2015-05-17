#ifndef CONVERTER_H
#define CONVERTER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int uint;

struct Vertex {
	float x, y, z; // w
};

struct TextureCoordinate {
	float u, v; // w
};

struct Normal {
	float x, y, z;
};

struct Face {
	uint vertex[3];
	uint texture[3];
	uint normal[3];
};

vector<Vertex> vertexes;
vector<TextureCoordinate> textureCoordinates;
vector<Normal> normals;
vector<Face> faces;

int main(int argc, char** args);

bool doInput(const char* path);
bool doOutput(const char* path);

void printInfo();

#endif