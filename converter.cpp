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
	}
	
	fclose(f);
	
	return true;
}

bool doOutput(const char* path) {
	return true;
}