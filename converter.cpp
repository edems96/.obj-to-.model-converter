#include "converter.h"

int main(int argc, char** args) {
	
	if( doInput("nap.obj") ) {
		printf("do Input ok\n");
		printInfo();
	}
	else
		printf("do Input not ok\n");
	
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
		
		//printf("buffer (%d): %s\n", buff.length(), buffer);
		
		if( buffer[0] == '#' )
			continue;
		else if( buffer[0] == 'v' && buffer[1] == ' ' ) {
			Vertex v;
			
			r = sscanf(buffer, 
				"v %f %f %f",
				&v.x,
				&v.y,
				&v.z);
				
			if( r > 0 )
				vertexes.push_back(v);
			else
				printf("Failed to read vertex property!\n");
		}
		else if( buffer[0] == 'v' && buffer[1] == 't' ) {
			TextureCoordinate tc;
			
			r = sscanf(buffer, 
				"vt %f %f",
				&tc.u,
				&tc.v);
				
			if( r > 0 )
				textureCoordinates.push_back(tc);
			else
				printf("Failed to read texture coordinate property!\n");
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
			else
				printf("Failed to read normal property!\n");
		}
		else if( buffer[0] == 'f' ) {
			Face f;
			
			r = sscanf(buffer,
				"f %d %d %d",
				&f.vertex[0],
				&f.vertex[1],
				&f.vertex[2]);
				
			if( r > 0 ) {
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
				
			if( r > 0 ) {
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
				
			if( r > 0 ) {
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
				
			if( r > 0 )
				faces.push_back(f);
			else
				printf("Failed to read face properly!\n");
		}
		
	}
	
	fclose(f);
	
	return true;
}

bool doOutput(const char* path) {
	return true;
}

void printInfo() {
	printf("#INFO#\n");
	printf("\tVertex count: %d\n", vertexes.size());
	printf("\tTextureCoordinate count: %d\n", textureCoordinates.size());
	printf("\tNormal count: %d\n", normals.size());
	printf("\tFace count: %d\n", faces.size());
	
	//printf("%f %f %f", normals[0].x, normals[1].y, normals[2].z);
}