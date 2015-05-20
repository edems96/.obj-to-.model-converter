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
	bool quad, 
		hasTextureCoordinate, 
		hasNormal;
	
	uint material;
	
	uint vertex[4];
	uint texture[4];
	uint normal[4];
	
	Face() : quad(false), hasTextureCoordinate(false), hasNormal(false), material(0) {}
};

struct Material {
	char name[64];
	
	float Ka[3]; // ambient color 
	float Kd[3]; // diffuse color
	float Ks[3]; // specular color
	float Ns; // specular exponent
	float d; // dissolved or Tr
	uint illum; // illumination models
	
	bool hasTexture;
	char map_Kd[64];
	
	Material() : hasTexture(false) {}
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

uint getMaterialId(const char *name);

void printInfo();

#endif