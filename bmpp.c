#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmpplib.h"

int main(int argc, char **argv) {
	/* fmt = (0 = pretty print, 1 = JSON) */
	int fmt = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <bitmap file>\n", argv[0]);
		return 1;
	}

	if (argc > 2 && strcmp(argv[2], "-json") == 0)
		fmt = 1;

	bmp_parse(argv[1], fmt);
}
