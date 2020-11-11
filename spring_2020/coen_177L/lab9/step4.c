#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buffer[atoi(argv[2])];
	char newFilename[100];
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "rb");
	sprintf(newFilename, "%s_copy.txt", argv[1]);
	fp2 = fopen(newFilename, "wb");
	while (fread(buffer, sizeof(buffer), 1, fp1)){
		fwrite(buffer, sizeof(buffer), 1, fp2);
	}
	fclose(fp1);
	fclose(fp2);
}
