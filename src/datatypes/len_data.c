#include <datatypes/len_data.h>

#include <stdint.h>

len_data_t *len_data(void *data, size_t sz)
{
	len_data_t *d = (len_data_t*)malloc(LEN_DATA_SIZE);

	d->len = sz;
	d->d = (char*)data;
}
