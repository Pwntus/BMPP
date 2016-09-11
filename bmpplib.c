#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmpplib.h"

void error(char *err_msg) {
	fprintf(stderr, "Error: %s\n", err_msg);
	exit(0);
}

static char * fmt_comp(uint32_t comp_num) {
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

	return C[comp_num];
}

static void print_json(header_t *a, info_header_t *b) {
	printf("{");
	printf("\"signature\":\"0x%X\",", (uint16_t)a->signature);
	printf("\"file_size\":%d,", (uint32_t)a->filesize);
	printf("\"reserved_1\":\"0x%X\",", (uint16_t)a->reserved_0);
	printf("\"reserved_2\":\"0x%X\",", (uint16_t)a->reserved_1);
	printf("\"offset\":\"0x%X\",", (uint32_t)a->offset);

	printf("\"info_size\":%d,", (uint32_t)b->size);
	printf("\"width\":%d,", (int32_t)b->width);
	printf("\"height\":%d,", (int32_t)b->height);
	printf("\"color_panels\":%d,", (uint16_t)b->n_cplanes);
	printf("\"bpp\":%d,", (uint16_t)b->n_bpp);
	printf("\"compression\":\"%d,%s\",", (uint32_t)b->compression, fmt_comp(b->compression));
	printf("\"img_size\":%d,", (uint32_t)b->img_size);
	printf("\"y_res\":%d,", (int32_t)b->y_res);
	printf("\"x_res\":%d,", (int32_t)b->x_res);
	printf("\"n_cpalette\":%d,", (uint32_t)b->n_cpalette);
	printf("\"n_important\":%d", (uint32_t)b->n_important);
	printf("}");
}

static void print_pretty(header_t *a, info_header_t *b) {
	printf("+-------------------------+\n");
	printf("| Signature               | 0x%X\n", (uint16_t)a->signature);
	printf("+-------------------------+\n");
	printf("| File size:              | %d bytes\n", (uint32_t)a->filesize);
	printf("+-------------------------+\n");
	printf("| Reserved 1              | 0x%X\n", (uint16_t)a->reserved_0);
	printf("+-------------------------+\n");
	printf("| Reserved 2              | 0x%X\n", (uint16_t)a->reserved_1);
	printf("+-------------------------+\n");
	printf("| Bitmap data offset      | 0x%X\n", (uint32_t)a->offset);
	printf("+-------------------------+\n");

	printf("| Info header size        | %d bytes\n", (uint32_t)b->size);
	printf("+-------------------------+\n");
	printf("| Bitmap width            | %dpx\n", (int32_t)b->width);
	printf("+-------------------------+\n");
	printf("| Bitmap height           | %dpx\n", (int32_t)b->height);
	printf("+-------------------------+\n");
	printf("| # color planes          | %d\n", (uint16_t)b->n_cplanes);
	printf("+-------------------------+\n");
	printf("| Image depth (bits / px) | %d\n", (uint16_t)b->n_bpp);
	printf("+-------------------------+\n");
	printf("| Compression             | %d (%s)\n", (uint32_t)b->compression, fmt_comp(b->compression));
	printf("+-------------------------+\n");
	printf("| Image size              | %d bytes\n", (uint32_t)b->img_size);
	printf("+-------------------------+\n");
	printf("| Y resolution (px / m)   | %d\n", (int32_t)b->y_res);
	printf("+-------------------------+\n");
	printf("| X resolution (px / m)   | %d\n", (int32_t)b->x_res);
	printf("+-------------------------+\n");
	printf("| # colors in palette     | %d\n", (uint32_t)b->n_cpalette);
	printf("+-------------------------+\n");
	printf("| # important colors      | %d\n", (uint32_t)b->n_important);
	printf("+-------------------------+\n");
}

uint8_t bmp_parse(char *bmp_fn, int fmt) {
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

	fclose(bmp_f);

	/* Print results */
	if (fmt > 0)
		print_json(&header, &info_header);
	else
		print_pretty(&header, &info_header);

	return 1;
}
