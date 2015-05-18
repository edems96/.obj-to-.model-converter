#include "converter.h"

int main(int argc, char** args) {
	char *input, *output;
	
	for(uint i = 1; i < argc; i++) {
		
		switch( args[i][1] ) {
			case 'i': 
				input = (char*) malloc(strlen(args[++i]));	
				memcpy(input, args[i], strlen(args[i]));
				break;
				
			case 'o': 
				output = (char*) malloc(strlen(args[++i]));	
				memcpy(output, args[i], strlen(args[i])); break;
		}
		
	}
	
	printf("Input file: %s\n", input);
	printf("Output file: %s\n", output);
	
	if( doInput(input) ) {
		
		if( doOutput(output) )
			printf("Successfully wrote out!");
		else
			printf("Failed to write output!");
		
	} else
		printf("Failed to read input!");
	
	return 1;
}

bool doInput(const char* path) {
	FILE *f;
	
	f = fopen(path, "r");
	
	if( f == NULL ) {
		printf("Failed to open file: %s\n", path);
		return false;
	}
	
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
		else if( buffer[0] == 'f' ) {
			Face f;
			f.quad = false;
			
			r = sscanf(buffer,
				"f %d %d %d",
				&f.vertex[0],
				&f.vertex[1],
				&f.vertex[2]);
				
			if( r == 3 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/ %d/%d/ %d/%d/",
				&f.vertex[0],
				&f.texture[0],
				&f.vertex[1],
				&f.texture[1],
				&f.vertex[2],
				&f.texture[2]);
				
			if( r == 6 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d//%d %d//%d %d//%d",
				&f.vertex[0],
				&f.normal[0],
				&f.vertex[1],
				&f.normal[1],
				&f.vertex[2],
				&f.normal[2]);
				
			if( r == 6 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/%d %d/%d/%d %d/%d/%d",
				&f.vertex[0],
				&f.texture[0],
				&f.normal[0],
				&f.vertex[1],
				&f.texture[1],
				&f.normal[1],
				&f.vertex[2],
				&f.texture[2],
				&f.normal[2]);
				
			if( r == 9 ) {
				faces.push_back(f);
				continue;
			}
			
			f.quad = true;
			
			r = sscanf(buffer,
				"f %d %d %d %d",
				&f.vertex[0],
				&f.vertex[1],
				&f.vertex[2],
				&f.vertex[3]);
				
			if( r == 4 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/ %d/%d/ %d/%d/ %d/%d/",
				&f.vertex[0],
				&f.texture[0],
				&f.vertex[1],
				&f.texture[1],
				&f.vertex[2],
				&f.texture[2],
				&f.vertex[3],
				&f.texture[3]);
				
			if( r == 8 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d//%d %d//%d %d//%d %d//%d",
				&f.vertex[0],
				&f.normal[0],
				&f.vertex[1],
				&f.normal[1],
				&f.vertex[2],
				&f.normal[2],
				&f.vertex[3],
				&f.normal[3]);
				
			if( r == 8 ) {
				faces.push_back(f);
				continue;
			}
			
			r = sscanf(buffer,
				"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&f.vertex[0],
				&f.texture[0],
				&f.normal[0],
				&f.vertex[1],
				&f.texture[1],
				&f.normal[1],
				&f.vertex[2],
				&f.texture[2],
				&f.normal[2],
				&f.vertex[3],
				&f.texture[3],
				&f.normal[3]);
				
			if( r == 12 ) 
				faces.push_back(f);
			else {
				printf("Failed to read face properly!\n");
				return false;
			}
			
		} else if( buffer[0] == 'm' ) {
			int r = sscanf(buffer,
				"mtllib %s", 
				&mtlLib.path);
			
			if( r != 1 )
				printf("Failed to read mtllib properly!\n");
			
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

	// VERTEX
	size = vertexes.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	for(uint i = 0; i < vertexes.size(); i++) {
		if( !fW(f, &vertexes[i], sizeof(Vertex)) )
			return false;
	}
	
	// TextureCoordinate
	size = textureCoordinates.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	for(uint i = 0; i < textureCoordinates.size(); i++) {
		if( !fW(f, &textureCoordinates[i], sizeof(TextureCoordinate)) )
			return false;
	}
	
	// Normal
	size = normals.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	for(uint i = 0; i < normals.size(); i++) {
		if( !fW(f, &normals[i], sizeof(Normal)) )
			return false;
	}
	
	// Face
	size = faces.size();
	if( !fW(f, &size, sizeof(uint)) )
		return false;
	
	for(uint i = 0; i < faces.size(); i++) {
		if( !fW(f, &faces[i], sizeof(Face)) )
			return false;
	}
	
	fclose(f);
	
	return true;
}

bool fW(FILE *f, const void * ptr, size_t size) {
	return fwrite(ptr, size, 1, f) == 1;
}

void printInfo() {
	printf("#INFO#\n");
	printf("\tVertex count: %d\n", vertexes.size());
	printf("\tTextureCoordinate count: %d\n", textureCoordinates.size());
	printf("\tNormal count: %d\n", normals.size());
	printf("\tFace count: %d\n", faces.size());
}