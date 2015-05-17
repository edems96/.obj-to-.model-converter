#include "converter.h"

int main(int argc, char** args) {
	
	return 1;
}

bool doInput(const char* path) {
	FILE *f;
	
	f = fopen(path, "r");
	
	if( f == NULL ) {
		printf("Failed to open file: %s\n", path);
		return false;
	}
	
	while( true ) {
		char buffer[256];
		
		int r = fscanf(f, "%s\n", buffer);
		
		if( r == EOF )
			break;
		
		if( buffer[0] == '#' )
			continue;
		else if( buffer[0] == 'v' && buffer[1] == ' ' ) {
			Vertex v;
			
			int r = sscanf(buffer, 
				"v %f %f %f",
				&v.x,
				&v.y,
				&v.z);
				
			if( r != EOF )
				vertexes.push_back(v);
			else
				printf("Failed to read vertex property!\n");
		}
		else if( buffer[0] == 'v' && buffer[1] == 't' ) {
			TextureCoordinate tc;
			
			int r = sscanf(buffer, 
				"vt %f %f",
				&tc.u,
				&tc.v);
				
			if( r != EOF )
				textureCoordinates.push_back(tc);
			else
				printf("Failed to read texture coordinate property!\n");
		}
		else if( buffer[0] == 'v' && buffer[1] == 'n' ) {
			Normal n;
			
			int r = sscanf(buffer,
				"vn %f %f %f",
				&n.x,
				&n.y,
				&n.z);
				
			if( r != EOF )
				normals.push_back(n);
			else
				printf("Failed to read normal property!\n");
		}
		else if( buffer[0] == 'f' ) {
			Face f;
			
			
		}
	}
	
	fclose(f);
	
	return true;
}

bool doOutput(const char* path) {
	return true;
}