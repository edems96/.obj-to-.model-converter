#ifndef CONVERTER_H
#define CONVERTER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

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
	bool quad;
	
	uint vertex[4];
	uint texture[4];
	uint normal[4];
};

struct MtlLib {
	char path[64];
	
	int length() { return strlen(path); }
};

const char *HEADER = "MODEL";
const ushort VERSION = 1;

vector<Vertex> vertexes;
vector<TextureCoordinate> textureCoordinates;
vector<Normal> normals;
vector<Face> faces;

MtlLib mtlLib;

int main(int argc, char** args);

bool doInput(const char* path);
bool doOutput(const char* path);
bool fW(FILE *f, const void * ptr, size_t size);

void printInfo();

#endif