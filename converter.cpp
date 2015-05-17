#include "converter.h"

int main(int argc, char** args) {
	
	if( doInput("nap.obj") )
		printf("do Input ok\n");
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
	
	while( true ) {
		char buffer[256];
		
		int r = fscanf(f, "%s\n", buffer);
		printf("buffer: %s\n", buffer);
		if( r == EOF )
			break;
		
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
			
			printf("r: %d\n", r);
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
				
			if( r > 0 )
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
		
		break;
	}
	
	fclose(f);
	
	return true;
}

bool doOutput(const char* path) {
	return true;
}