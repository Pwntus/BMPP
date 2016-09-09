#ifndef BMPPLIB_H
#define BMPP_LIB

#include <stdint.h>

void error(char *error_msg);
uint8_t bmp_parse(char *bmp_fn);

typedef struct header_t {
	uint16_t 	signature;
	uint32_t 	filesize;
	uint16_t	reserved_0;
	uint16_t	reserved_1;
	uint32_t	offset;
} __attribute__((packed)) header_t;

typedef struct info_header_t {
	uint32_t 	size;
	int32_t 	width;
	int32_t 	height;
	uint16_t	n_cplanes;
	uint16_t	n_bpp;
	uint32_t	compression;
	uint32_t	img_size;
	int32_t		y_res;
	int32_t		x_res;
	uint32_t	n_cpalette;
	uint32_t	n_important;
} __attribute__((packed)) info_header_t;

enum {
	BMP_FILE_HEADER_OFFSET = 0,
	BMP_INFO_HEADER_OFFSET = sizeof(header_t)
};

#endif /* !BMPPLIB_H */
