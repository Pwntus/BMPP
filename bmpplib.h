#ifndef BMPPLIB_H
#define BMPP_LIB

#include <stdint.h>

enum {
	BMP_FILE_HEADER_OFFSET = 0
};

typedef struct file_header_t {
	uint16_t 	signature;
	uint32_t 	filesize;
	uint16_t	reserved_0;
	uint16_t	reserved_1;
	uint32_t	offset;
} file_header_t;

void error(char *error_msg);
FILE * bmp_open(char *bmp_fn);
void bmp_read(void *data, FILE *file, size_t size);
uint8_t bmp_parse(char *bmp_fn);

void read_file_header(file_header_t *data, FILE *file);

#endif /* !BMPPLIB_H */
