#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buffer[atoi(argv[2])];
	FILE *fp;
	fp = fopen(argv[1], "rb");
	while (fread(buffer, sizeof(buffer), 1, fp)){
	
	}
	fclose(fp);
}
