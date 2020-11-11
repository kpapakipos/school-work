#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int pageno;
	int shield;
} ref_page;

int indx;

void setShieldOnPage(int pageno, ref_page *cache, int len);
void replaceFirstUnshielded(int pageno, ref_page *cache, int len);
int pageInCache(int pageno, ref_page *cache, int len);

int main(int argc, char *argv[]) {
	int cacheSize = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[cacheSize]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    int i;
    int totalFaults = 0; // keeps track of the total page faults

    for (i = 0; i < cacheSize; i++) { // initialise cache array
		cache[i].pageno = -1;
		cache[i].shield = 0;
	}
    
	indx = 0;
    while (fgets(pageCache, 100, stdin)) {
    	int pageno = atoi(pageCache); // Stores number read from file as an int
		// Page replacement implementation
		if (!pageInCache(pageno, cache, cacheSize)) { // page not in cache
			totalFaults += 1;
			replaceFirstUnshielded(pageno, cache, cacheSize);
		}
		else // page already in cache
			setShieldOnPage(pageno, cache, cacheSize);
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}

// find the given page in the cache, and set its shield bit to 1
void setShieldOnPage(int pageno, ref_page *cache, int len) {
	int i;
    for (i=0; i < len; i++) {
        if (pageno == cache[i].pageno) {
            cache[i].shield = 1;
			break;
		}
	}
}

// looks for a slot with no second chance / shield. When found, replace that value
// NOTE: when a new value is added, it is unshielded. Second chance bit is 0.
void replaceFirstUnshielded(int pageno, ref_page *cache, int len) {
    while (1) {
		if (!cache[indx % len].shield) { // this slot unshielded
			cache[indx % len].pageno = pageno;
			indx++;
			break;
		}
		else { // this slot shielded
			cache[indx % len].shield = 0;
			indx++;
		}
	}
}

// is given page number in the cache already? 0 for no, 1 for yes
int pageInCache(int pageno, ref_page *cache, int len) {
    int i;
    for (i=0; i < len; i++)
        if (pageno == cache[i].pageno)
            return 1;
    return 0;
}
