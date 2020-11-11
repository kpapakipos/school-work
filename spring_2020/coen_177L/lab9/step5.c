#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct funArg { 
	char **argv; 
	int *uniqueNum;
};

pthread_t *threads;
int nums[64];
struct funArg funArgs[64];

void *go(void *arg) {
	char **argv = ((struct funArg*)arg)->argv;
	char buffer[atoi(argv[2])];
	char newFilename[100];
	int uniqueNum = *(((struct funArg*)arg)->uniqueNum);
	//sprintf(newFilename, "%s_copy_%d_%d_%d.txt", argv[1], atoi(argv[2]), atoi(argv[3]), uniqueNum);
    sprintf(newFilename, "%s_copy_%d.txt", argv[1], uniqueNum);
	FILE *fp1 = fopen(argv[1], "rb");
    FILE *fp2 = fopen(newFilename, "wb");
    while (fread(buffer, sizeof(buffer), 1, fp1)) {
        fwrite(buffer, sizeof(buffer), 1, fp2);
    }
	fclose(fp1);
    fclose(fp2);	
	return (NULL);
}

int main(int argc, char *argv[]) {
	threads = (pthread_t*)malloc(atoi(argv[3]) * sizeof(pthread_t));
	int i;
	int numThreads = atoi(argv[3]);
	for (i=0; i < numThreads; i++) {
		nums[i] = i;
		funArgs[i].argv = argv;
		funArgs[i].uniqueNum = &nums[i];
		pthread_create(&threads[i], NULL, go, &funArgs[i]);
	}
	for (i=0; i < numThreads; i++)
		pthread_join(threads[i], NULL);
	free(threads);
}
