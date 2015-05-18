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

struct Material {
	char name[64];
	
	float Ka[3]; // ambient color 
	float Kd[3]; // diffuse color
	float Ks[3]; // specular color
	float Ns; // specular exponent
	float d; // dissolved or Tr
	uint illum; // illumination models
};

const char *HEADER = "MODEL";
const ushort VERSION = 1;

vector<Vertex> vertexes;
vector<TextureCoordinate> textureCoordinates;
vector<Normal> normals;
vector<Face> faces;
vector<Material> materials;

int main(int argc, char** args);

bool doInput(const char* path);
bool doOutput(const char* path);
bool readMtlLib(const char* path);

bool fW(FILE *f, const void * ptr, size_t size);

void printInfo();

#endif