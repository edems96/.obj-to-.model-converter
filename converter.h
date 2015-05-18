#ifndef CONVERTER_H
#define CONVERTER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#define HEADER "MODEL"

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
	uint vertex[4];
	uint texture[4];
	uint normal[4];
	
	bool quad;
};

struct MtlLib {
	char path[64];
	
	int length() { return strlen(path); }
};

vector<Vertex> vertexes;
vector<TextureCoordinate> textureCoordinates;
vector<Normal> normals;
vector<Face> faces;

MtlLib mtlLib;

int main(int argc, char** args);

bool doInput(const char* path);
bool doOutput(const char* path);

void printInfo();

#endif