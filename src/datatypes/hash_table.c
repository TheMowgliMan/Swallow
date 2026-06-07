#include <datatypes/hash_table.h>

#include <datatpyes/len_data.h>

#include <stdlib.h>
#include <stdint.h>

uint64_t hash_table_sizes[11] = {
    67,
    149,
    257,
    521,
    1033,
    4253,
    7919,
    16661,
    74747,
    371951,
    1869209
};

const int TABLE_SIZES = 11;

uint64_t __find_best_size(size_t sz)
{
    long index = 0;
    while (hash_table_sizes[index] < sz)
    {
        if (index > TABLE_SIZES)
            return 0;
        index++;
    }

    return hash_table_sizes[index];
}

hash_table_t *hash_table_create(size_t size_hint)
{
    hash_table_t *table = (hash_table_t*)malloc(HASH_TABLE_SIZE);
    if (table == NULL)
        return NULL;

    table->arrused = 0;

    size_t entries_to_allocate = __find_best_size(size_hint);
    table->arrsz = entries_to_allocate;
    table->arr = calloc(entries_to_allocate, sizeof(void*));

	table->colls = NULL;

    return table;
}

void hash_table_destroy(hash_table_t *tctx)
{
    if (tctx == NULL)
        return;

	if (tctx->colls != NULL) {
		hash_table_destroy(tctx->colls);
	}

    if (tctx->arr == NULL)
        goto free_table;

    free(tctx->arr);

free_table:
    free(tctx);
}

static uint64_t __xorshift_char(char *c)
{
    return (uint64_t)(*c) * 0x2545f4914f6cdd1dull;
}

static uint64_t __hash_len_data(len_data_t *ldctx)
{
    uint64_t ret = 99194853094755497ull;
	uint64_t len = len_data_size(ldctx);

	char *data = len_data_get(ldctx);
	
    for (uint64_t i = 0; i < len; i++)
    {
        ret ^= __xorshift_char(&cstr[i]) << 3;
    }

    return ret;
}

uint8_t __is_collision(hash_table_t *tblctx, uint64_t hash)
{
	uint64_t insert = hash % tblctx->arrsz;

	if (tblctx->arr[insert] != NULL) {
		return 1;
	} else {
		return 0;
	}
}

void __register_collision(hash_table_t *tblctx, len_data_t *key, uint64_t hash)
{
	len_data_t *invdata = len_data_bitnot(key);

	if (tblctx->colls == NULL) {
		hash_table_t *colls = hash_table_create(HASH_TABLE_COLLISION_SIZE_HINT);
		tblctx->colls = colls;
	}

	hash_table_insert(tblctx->colls, invdata, )
	
	len_data_destroy(invdata);
}

void hash_table_insert(hash_table_t *tblctx, len_data_t *key, len_data_t *val)
{
    if (tblctx->arrused > MULT_FRAC(tblctx->arrsz, 3, 4))
    {
        newctx = hash_table_create(MULT_FRAC(tblctx->arrsz, 3, 2));
    }

    uint64_t hash = __hash_len_data(key);
    uint64_t insert = hash % tblctx->arrsz;
}
