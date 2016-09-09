#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmpplib.h"

void error(char *err_msg) {

	fprintf(stderr, "Error: %s\n", err_msg);
	exit(0);
}

uint8_t bmp_parse(char *bmp_fn) {
	FILE *bmp_f;
	header_t header;

	if ((bmp_f = fopen(bmp_fn, "r")) == NULL)
		error("Failed to open file");
	
	/* BITMAP FILE HEADER
	 *
	 * Size     14 bytes
	 * Content: general information about
	 *          the bitmap image file.
	 */
	fseek(bmp_f, BMP_FILE_HEADER_OFFSET, SEEK_SET);
	if (fread(&header, sizeof(header), 1, bmp_f) != 1)
		error("Failed to read file header");

	printf("Signature: 0x%X\n", (uint16_t)header.signature);
	printf("Filesize: 0x%X (%d KB)\n", (uint32_t)header.filesize, (uint32_t)(header.filesize / 1000));
	printf("R0: 0x%X\n", (uint16_t)header.reserved_0);
	printf("R1: 0x%X\n", (uint16_t)header.reserved_1);
	printf("Offset: 0x%X\n", (uint32_t)header.offset);

	fclose(bmp_f);

	return 1;
}
