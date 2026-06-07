#include <datatypes/len_data.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

len_data_t *len_data(void *data, size_t sz)
{
	len_data_t *d = (len_data_t*)malloc(LEN_DATA_SIZE);

	d->len = sz;
	d->d = (char*)data;
	d->is_str = 0;

	return d;
}

len_data_t *len_data_copy(void *data, size_t sz)
{
	char *o = (char*)malloc(sz * sizeof(char));
	memcpy(o, data, sz);

	return len_data(o, sz);
}

len_data_t *len_data_cstr(char *data)
{
	size_t str_sz = strlen(data);
	char *o = (char*)malloc(str_sz * sizeof(char));
	memcpy(o, data, str_sz);

	len_data_t *ret = len_data(o, str_size);
	ret->is_str = 1;

	return ret;
}

char *len_data_to_cstr(len_data_t *ldctx)
{
	if (ldctx->is_str) {
		// Using calloc takes care of the null-terminator for us
		char *c = (char*)calloc(len_data_size(ldctx) + 1, sizeof(char));
		memcpy(c, ldctx->d, len_data_size(ldctx));

		return c;
	}

	char *c = (char*)malloc(256 * sizeof(char));
	snprintf(c,
			 256,
			 "<len_data_t object @ %p of size %d with data @ %p>",
			 (void*)ldctx,
			 (int)len_data_size(ldctx),
			 (void*)(ldctx->d));

	return c;
}

len_data_t *len_data_bitnot(len_data_t *ldctx)
{
	char *d = len_data_get(ldctx);
	size_t sz = len_data_size(ldctx);

	char *new_data = malloc(sizeof(char) * sz);

	for (uint64_t i = 0; i < sz; i++) {
		new_data[i] = ~d[i];
	}

	ret = len_data(new_data, sz);
	ret->is_str = ldctx->is_str;

	return ret;
}

void *len_data_destroy(len_data_t *ldctx)
{
	free(ldctx->d);
	free(ldctx);
}
