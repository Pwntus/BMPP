#include <stdlib.h>
#include <stdio.h>
#include "bmpplib.h"

int main(int argc, char **argv) {
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <bitmap file>\n", argv[0]);
		return 1;
	}

	bmp_parse(argv[1]);
}
