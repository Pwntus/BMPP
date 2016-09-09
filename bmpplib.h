#ifndef BMPPLIB_H
#define BMPP_LIB

#include <stdint.h>

enum {
	BMP_FILE_HEADER_OFFSET = 0
};

typedef struct header_t {
	uint16_t 	signature;
	uint32_t 	filesize;
	uint16_t	reserved_0;
	uint16_t	reserved_1;
	uint32_t	offset;
} __attribute__((packed)) header_t;

void error(char *error_msg);
uint8_t bmp_parse(char *bmp_fn);

#endif /* !BMPPLIB_H */
