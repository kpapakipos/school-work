#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int pageno;
} ref_page;

void removePageAndShift(int pageno, ref_page *cache, int len);
void popAndShift(ref_page *cache, int len);
int pageInCache(int pageno, ref_page *cache, int len);
int pushPage(int pageno, ref_page *cache, int len);

int main(int argc, char *argv[]) {
	int cacheSize = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[cacheSize]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    int i;
    int totalFaults = 0; // keeps track of the total page faults

    for (i = 0; i < cacheSize; i++) // initialise cache array
		cache[i].pageno = -1;
    
    while (fgets(pageCache, 100, stdin)) {
    	int pageno = atoi(pageCache); // Stores number read from file as an int
		// Page replacement implementation
		if (!pageInCache(pageno, cache, cacheSize)) { // page not in cache
			totalFaults += 1;
			if (!pushPage(pageno, cache, cacheSize)) { // no empty slots
				popAndShift(cache, cacheSize);
				pushPage(pageno, cache, cacheSize);
			}
		}
		else { // page in cache already- remove from position and push to rear
			removePageAndShift(pageno, cache, cacheSize);
			pushPage(pageno, cache, cacheSize);
		}
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}

// search from left of cache to right for given pageno. When found, remove, shift
// remaining pages one slot to the left. 
void removePageAndShift(int pageno, ref_page *cache, int len) {
	int i;
	for (i=0; i < len - 1; i++) {
        if (cache[i].pageno == -1)
            break;
		if (cache[i].pageno == pageno) {
			popAndShift(&cache[i], len - i);
			break;
		}
	}
}

// remove first page in cache and then shift all others one to the left
void popAndShift(ref_page *cache, int len) {
    int i, removedNo = cache[0].pageno;
    for (i=0; i < len - 1; i++) {
        if (cache[i].pageno == -1)
            break;
        cache[i].pageno = cache[i+1].pageno;
    }
    cache[len-1].pageno = -1;
}

// is given page number in the cache already? 0 for no, 1 for yes
int pageInCache(int pageno, ref_page *cache, int len) {
    int i;
    for (i=0; i < len; i++)
        if (pageno == cache[i].pageno)
            return 1;
    return 0;
}

// put new page in leftmost empty slot. 0 if no empty slots, 1 if so.
int pushPage(int pageno, ref_page *cache, int len) {
    int i;
    for (i=0; i < len; i++) {
        if (cache[i].pageno == -1) {
            cache[i].pageno = pageno;
            return 1;
        }
    }
    return 0;
}
