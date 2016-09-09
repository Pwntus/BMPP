#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmpplib.h"

void error(char *err_msg) {

	fprintf(stderr, "Error: %s\n", err_msg);
	exit(0);
}

static char * fmt_comp(uint32_t *comp_num) {
	char *C[14];
	C[0] = "BI_RGB";
	C[1] = "BI_RLE8";
	C[2] = "BI_RLE4";
	C[3] = "BI_BITFIELDS";
	C[4] = "BI_JPEG";
	C[5] = "BI_PNG";
	C[6] = "BI_ALPHABITFIELDS";
	C[7] = "UNKNOWN";
	C[8] = "UNKNOWN";
	C[9] = "UNKNOWN";
	C[10] = "UNKNOWN";
	C[11] = "BI_CMYK";
	C[12] = "BI_CMYKRLE8";
	C[13] = "BI_CMYKRLE4";

	return C[*comp_num];
}

uint8_t bmp_parse(char *bmp_fn) {
	FILE *bmp_f;
	header_t header;
	info_header_t info_header;

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
	printf("Filesize: %d bytes (%d KB)\n", (uint32_t)header.filesize, (uint32_t)(header.filesize / 1000));
	printf("Reserved 1: 0x%X\n", (uint16_t)header.reserved_0);
	printf("Reserved 2: 0x%X\n", (uint16_t)header.reserved_1);
	printf("Bitmap data offset: 0x%X\n", (uint32_t)header.offset);

	/* BITMAP INFO HEADER
	 *
	 * Size     40 bytes
	 * Content: detailed information about
	 *          the image. Used by image
	 *          processing applications.
	 */
	fseek(bmp_f, BMP_INFO_HEADER_OFFSET, SEEK_SET);
	if (fread(&info_header, sizeof(info_header), 1, bmp_f) != 1)
		error("Failed to read info header");

	printf("____________________________\n");
	printf("Info header size: %d bytes\n", (uint32_t)info_header.size);
	printf("Bitmap width: %dpx\n", (int32_t)info_header.width);
	printf("Bitmap height: %dpx\n", (int32_t)info_header.height);
	printf("# color planes: %d\n", (uint16_t)info_header.n_cplanes);
	printf("Image depth (bits / px): %d\n", (uint16_t)info_header.n_bpp);
	printf("Compression: %d (%s)\n", (uint32_t)info_header.compression, fmt_comp(&info_header.compression));
	printf("Image size: %d bytes (%d KB)\n", (uint32_t)info_header.img_size, (uint32_t)(info_header.img_size / 1000));
	printf("Y resolution (px / m): %d\n", (int32_t)info_header.y_res);
	printf("X resolution (px / m): %d\n", (int32_t)info_header.x_res);
	printf("# colors in palette: %d\n", (uint32_t)info_header.n_cpalette);
	printf("# important colors: %d\n", (uint32_t)info_header.n_important);

	fclose(bmp_f);

	return 1;
}
