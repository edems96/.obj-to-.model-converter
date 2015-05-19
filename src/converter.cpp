#include "converter.h"

int main(int argc, char** args) {
	string input, output;
	
	for(uint i = 1; i < argc; i++) {
		
		switch( args[i][1] ) {
			case 'i': input = args[++i]; break;
			case 'o': output = args[++i]; break;
		}
		
	}
	
	printf("Input file: %s\n", input.c_str());
	printf("Output file: %s\n", output.c_str());
	
	printf("\n");
	
	if( doInput(input.c_str()) ) {
		
		if( doOutput(output.c_str()) )
			printf("Successfully write output!\n");
		else
			printf("Failed to write output!\n");
		
	} else
		printf("Failed to read input!\n");
	
	return 1;
}

bool doInput(const char* path) {
	FILE *f;
	
	f = fopen(path, "r");
	
	if( f == NULL ) {
		printf("Failed to open file: %s\n", path);
		return false;
	}
	
	uint material = 0;
	while( !feof(f) ) {
		string buff;
		int r;
		
		while( true ) {
			r = fgetc(f);
			
			if( r == EOF || r == '\n' ) {
				break;
			}
			
			buff.push_back(r);
		}
		
		const char* buffer = buff.c_str();
		
		if( buffer[0] == '#' )
			continue;
		else if( buffer[0] == 'v' && buffer[1] == ' ' ) {
			Vertex v;
			
			r = sscanf(buffer, 
				"v %f %f %f",
				&v.x,
				&v.y,
				&v.z);
				
			if( r == 3 )
				vertexes.push_back(v);
			else {
				printf("Failed to read vertex property!\n");
				return false;
			}
			
		}
		else if( buffer[0] == 'v' && buffer[1] == 't' ) {
			TextureCoordinate tc;
			
			r = sscanf(buffer, 
				"vt %f %f",
				&tc.u,
				&tc.v);
				
			if( r == 2 )
				textureCoordinates.push_back(tc);
			else {
				printf("Failed to read texture coordinate property!\n");
				return false;
			}
			
		}
		else if( buffer[0] == 'v' && buffer[1] == 'n' ) {
			Normal n;

			r = sscanf(buffer,
				"vn %f %f %f",
				&n.x,
				&n.y,
				&n.z);
				
			if( r == 3 )
				normals.push_back(n);
			else {
				printf("Failed to read normal property!\n");
				return false;
			}
			
		}
		else if( buffer[0] == 'f' && buffer[1] == ' ' ) {
			Face face;
			face.quad = true;
			face.material = material;
			
			// quad
			r = sscanf(buffer,
				"f %d %d %d %d",
				&face.vertex[0],
				&face.vertex[1],
				&face.vertex[2],
				&face.vertex[3]);
				
			if( r == 4 ) {
				face.hasTextureCoordinate = false;
				face.hasNormal = false;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/ %d/%d/ %d/%d/ %d/%d/",
				&face.vertex[0],
				&face.texture[0],
				&face.vertex[1],
				&face.texture[1],
				&face.vertex[2],
				&face.texture[2],
				&face.vertex[3],
				&face.texture[3]);
				
			if( r == 8 ) {
				face.hasTextureCoordinate = true;
				face.hasNormal = false;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d//%d %d//%d %d//%d %d//%d",
				&face.vertex[0],
				&face.normal[0],
				&face.vertex[1],
				&face.normal[1],
				&face.vertex[2],
				&face.normal[2],
				&face.vertex[3],
				&face.normal[3]);
				
			if( r == 8 ) {
				face.hasTextureCoordinate = false;
				face.hasNormal = true;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.vertex[0],
				&face.texture[0],
				&face.normal[0],
				&face.vertex[1],
				&face.texture[1],
				&face.normal[1],
				&face.vertex[2],
				&face.texture[2],
				&face.normal[2],
				&face.vertex[3],
				&face.texture[3],
				&face.normal[3]);
				
			if( r == 12 ) {
				face.hasTextureCoordinate = true;
				face.hasNormal = true;
				
				faces.push_back(face);
				continue;
			}
			
			face.quad = false;
			
			// triangle
			r = sscanf(buffer,
				"f %d %d %d",
				&face.vertex[0],
				&face.vertex[1],
				&face.vertex[2]);
				
			if( r == 3 ) {
				face.hasTextureCoordinate = false;
				face.hasNormal = false;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/ %d/%d/ %d/%d/",
				&face.vertex[0],
				&face.texture[0],
				&face.vertex[1],
				&face.texture[1],
				&face.vertex[2],
				&face.texture[2]);
				
			if( r == 6 ) {
				face.hasTextureCoordinate = true;
				face.hasNormal = false;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d//%d %d//%d %d//%d",
				&face.vertex[0],
				&face.normal[0],
				&face.vertex[1],
				&face.normal[1],
				&face.vertex[2],
				&face.normal[2]);
				
			if( r == 6 ) {
				face.hasTextureCoordinate = false;
				face.hasNormal = true;
				
				faces.push_back(face);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.vertex[0],
				&face.texture[0],
				&face.normal[0],
				&face.vertex[1],
				&face.texture[1],
				&face.normal[1],
				&face.vertex[2],
				&face.texture[2],
				&face.normal[2]);
				
			if( r == 9 ) {
				face.hasTextureCoordinate = true;
				face.hasNormal = true;
				
				faces.push_back(face);
			}
			else {
				printf("Failed to read face properly!\n");
				return false;
			}
			
		} 
		else if( buffer[0] == 'm' && buffer[1] == 't' && buffer[2] == 'l' ) {
			char lib[64];
			
			r = sscanf(buffer,
				"mtllib %s", 
				lib);
			
			if( r != 1 )
				printf("Failed to read mtllib properly!\n");
			else {
				if( !readMtlLib(lib) ) {
					printf("Failed to read mtl lib!\n");
					return false;
				}
			}
	
		}
		else if( buffer[0] == 'u' && buffer[1] == 's' && buffer[2] == 'e' ) {
			char name[64];
			
			r = sscanf(buffer,
				"usemtl %s",
				name);
				
			if( r == 1 ) {
				material = getMaterialId(name);
			} else {
				printf("Failed to read & use material!\n");
				return false;
			}
		}
		
	}
	
	fclose(f);
	
	return true;
}

bool readMtlLib(const char* path) {
	FILE *f;
	
	f = fopen(path, "r");
	
	if( f == NULL ) {
		printf("Failed to open file: %s\n", path);
		return false;
	}
	
	printf("Reading %s mtllib file!\n", path);
	
	while( !feof(f) ) {
		string buff;
		int r;
		
		while( true ) {
			r = fgetc(f);
			
			if( r == EOF || r == '\n' ) {
				break;
			}
			
			buff.push_back(r);
		}
		
		const char* buffer = buff.c_str();
		
		if( buffer[0] == '#' || strlen(buffer) == 0 )
			continue;
		else if( buffer[0] == 'n' && buffer[1] == 'e' && buffer[2] == 'w' ) {
			Material m;
			
			r = sscanf(buffer,
				"newmtl %s",
				&m.name);
				
			if( r != 1 ) {
				printf("Failed to read material name properly!\n");
				return false;
			} else {
				materials.push_back(m);
			}
		}
		else if( buffer[0] == 'K' && buffer[1] == 'a' ) {
			r = sscanf(buffer,
				"Ka %f %f %f",
				&materials[materials.size()-1].Ka[0],
				&materials[materials.size()-1].Ka[1],
				&materials[materials.size()-1].Ka[2]);
				
			if( r != 3 ) {
				printf("Failed to read material's ambient color properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'K' && buffer[1] == 'd' ) {
			r = sscanf(buffer,
				"Kd %f %f %f",
				&materials[materials.size()-1].Kd[0],
				&materials[materials.size()-1].Kd[1],
				&materials[materials.size()-1].Kd[2]);
				
			if( r != 3 ) {
				printf("Failed to read material's diffuse color properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'K' && buffer[1] == 's' ) {
			r = sscanf(buffer,
				"Ks %f %f %f",
				&materials[materials.size()-1].Ks[0],
				&materials[materials.size()-1].Ks[1],
				&materials[materials.size()-1].Ks[2]);
				
			if( r != 3 ) {
				printf("Failed to read material's specular color properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'N' && buffer[1] == 's' ) {
			r = sscanf(buffer,
				"Ns %f",
				&materials[materials.size()-1].Ns);
				
			if( r != 1 ) {
				printf("Failed to read material's specular exponent properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'd' ) {
			r = sscanf(buffer,
				"d %f",
				&materials[materials.size()-1].d);
				
			if( r != 1 ) {
				printf("Failed to read material's dissolved properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'i' && buffer[1] == 'l' ) {
			r = sscanf(buffer,
				"illum %d",
				&materials[materials.size()-1].illum);
				
			if( r != 1 ) {
				printf("Failed to read material's illumination models properly!\n");
				return false;
			}
		}
		else if( buffer[0] == 'm' && buffer[1] == 'a' && buffer[2] == 'p' ) {
			char in[64];
			
			r = sscanf(buffer,
				"map_Kd %s",
				&in);
				
			if( r == 1 ) {
				string map_Kd = in;
				size_t pos = map_Kd.find_last_of("/\\");

				if( pos == string::npos )
					strcpy(materials[materials.size()-1].map_Kd, map_Kd.c_str());
				else
					strcpy(materials[materials.size()-1].map_Kd, map_Kd.substr(pos + 1).c_str());
			}
		}
	}
	
	fclose(f);
	
	return true;
}

bool doOutput(const char* path) {
	FILE *f;
	f = fopen(path, "wb+");
	
	if( f == NULL ) {
		printf("Failed to open file for write: %s\n", path);
		return false;
	}
	
	if( !fW(f, HEADER, strlen(HEADER)) )
		return false;
	
	if( !fW(f, &VERSION, sizeof(ushort)) )
		return false;
	
	uint size;
	
	size = vertexes.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	size = textureCoordinates.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	size = normals.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	size = faces.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	size = materials.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	
	// VERTEX
	for(uint i = 0; i < vertexes.size(); i++) {
		if( !fW(f, &vertexes[i], sizeof(Vertex)) )
			return false;
	}
	
	// TextureCoordinate
	for(uint i = 0; i < textureCoordinates.size(); i++) {
		if( !fW(f, &textureCoordinates[i], sizeof(TextureCoordinate)) )
			return false;
	}
	
	// Normal
	for(uint i = 0; i < normals.size(); i++) {
		if( !fW(f, &normals[i], sizeof(Normal)) )
			return false;
	}
	
	// Face
	for(uint i = 0; i < faces.size(); i++) {
		if( !fW(f, &faces[i], sizeof(Face)) )
			return false;
	}
	
	// Material
	for(uint i = 0; i < materials.size(); i++) {
		if( !fW(f, &materials[i], sizeof(Material)) )
			return false;
	}
	
	fclose(f);
	
	return true;
}

bool fW(FILE *f, const void * ptr, size_t size) {
	return fwrite(ptr, size, 1, f) == 1;
}

uint getMaterialId(const char *name) {
	for(uint i = 0; i < materials.size(); i++) {
		if( strcmp(materials[i].name, name) == 0 )
			return i + 1;
	}
	
	return 0;
}

void printInfo() {
	printf("#INFO#\n");
	printf("\tVertex count: %d\n", vertexes.size());
	printf("\tTextureCoordinate count: %d\n", textureCoordinates.size());
	printf("\tNormal count: %d\n", normals.size());
	printf("\tFace count: %d\n", faces.size());
}