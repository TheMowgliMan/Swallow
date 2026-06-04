#ifndef LEN_DATA_H_
#define LEN_DATA_H

#include <stdint.h>
#include <stdint.h>

#define LEN_DATA_SIZE sizeof(len_data_t)

typedef struct {
	char *d;
	size_t len;
} len_data_t;

#endif
