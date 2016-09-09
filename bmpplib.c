#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmpplib.h"

void error(char *err_msg) {

	fprintf(stderr, "Error: %s\n", err_msg);
	exit(0);
}

FILE * bmp_open(char *bmp_fn) {

	FILE *bmp_f = fopen(bmp_fn, "r");
	if (bmp_f == NULL)
		error("Failed to open file");

	return bmp_f;
}

void bmp_read(void *data, FILE *file, size_t size) {
	fread(data, size, 1, file);
}

void read_file_header(file_header_t *data, FILE *file) {
	fseek(file, BMP_FILE_HEADER_OFFSET, SEEK_SET);

	bmp_read(&data->signature, file, sizeof(data->signature));
	bmp_read(&data->filesize, file, sizeof(data->filesize));
	bmp_read(&data->reserved_0, file, sizeof(data->reserved_0));
	bmp_read(&data->reserved_1, file, sizeof(data->reserved_1));
	bmp_read(&data->offset, file, sizeof(data->offset));
}

uint8_t bmp_parse(char *bmp_fn) {
	FILE *bmp_f;

	file_header_t file_header;

	if (bmp_fn == NULL)
		error("Bitmap file name");

	bmp_f = bmp_open(bmp_fn);
	
	/* BITMAP FILE HEADER
	*
	 * Size: 	14 bytes
	 * Content:	general information about
	 *			the bitmap image file.
	 */
	read_file_header(&file_header, bmp_f);

	printf("Signature: 0x%X\n", (uint16_t)file_header.signature);
	printf("Filesize: 0x%X (%d KB)\n", (uint32_t)file_header.filesize, (uint32_t)(file_header.filesize / 1000));
	printf("R0: 0x%X\n", (uint16_t)file_header.reserved_0);
	printf("R1: 0x%X\n", (uint16_t)file_header.reserved_1);
	printf("Offset: 0x%X\n", (uint32_t)file_header.offset);

	return 1;
}
