#ifndef LEN_DATA_H_
#define LEN_DATA_H

#include <stdint.h>
#include <stdlib.h>

#define LEN_DATA_SIZE sizeof(len_data_t)

typedef struct {
	char *d;
	size_t len;
	uint8_t is_str;
} len_data_t;

/*
  Convert any data to a sized anonymous object.
  Parameters:
  - void *data: the data.
  - size_t sz: the size of the data.

  Returns:
  (len_data_t*): the data object.
*/
len_data_t *len_data(void *data, size_t sz);

/*
  Copy any data to a sized anonymous object.
  Parameters:
  - void *data: the data.
  - size_t sz: the size of the data.

  Returns:
  (len_data_t*): the data object.

  Remarks:
  - Note that this is slower and uses more memory than len_data(), so only use if you cannot ensure
  that the data will still exist during the lifetime of the object, or if you need a complete copy
  that will not change with changes to the underlying data.
*/
len_data_t *len_data_copy(void *data, size_t sz);

/*
  Copy a c-string into a sized anonymous object.
  Parameters:
  - char *cstr: the c-string to copy.

  Returns:
  (len_data_t*): the data object.

  Remarks:
  - Always copies the string.
*/
len_data_t *len_data_cstr(char *cstr);

/*
  Checks to see if a len_data_t object is a string.
  Parameters:
  - len_data_t *ldctx: the data to check.

  Returns:
  (uint8_t): 1 if string, 0 otherwise.
*/
inline static uint8_t len_data_is_str(len_data_t *ldctx)
{
	return ldctx->is_str;
}

/*
  Creates a c-string representing the len_data_t object.
  Parameters:
  - len_data_t *ldctx: the object to convert.

  Returns:
  (char*): the string representation of the object.

  Remarks:
  - If the object is a string, it creates a c-string representing the data. Otherwise, it creates
  a c-string representing the location and size of the object and its data.
*/
char *len_data_to_cstr(len_data_t *ldctx);

inline static size_t len_data_size(len_data_t *ldctx)
{
	return ldctx->len;
}

inline static char *len_data_get(len_data_t *ldctx)
{
	return ldctx->d;
}

#endif
