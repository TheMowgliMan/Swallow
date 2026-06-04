#include <datatypes/hash_table.h>

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

    return table;
}

void hash_table_destroy(hash_table_t *tctx)
{
    if (tctx == NULL)
        return;

    if (tctx->arr == NULL)
        goto free_table;

    free(tctx->arr);

free_table:
    free(tctx);
}

static uint64_t __xorshift_char(char *c)
{
    uint64_t ret = (uint64_t)(c[0]) * 0x2545F4914F6CDD1DULL;
    ret ^= ret >> 12;
    ret ^= ret << 25;
    ret ^= ret >> 27;

    return ret * 0x2545F4914F6CDD1DULL;
}

static uint64_t __hash_cstring(char *cstr)
{
    uint64_t ret = 99194853094755497ull;
    for (uint64_t i = 0; cstr[i] != 0; i++)
    {
        ret ^= __xorshift_char(&cstr[i]);
    }

    return ret;
}

void hash_table_insert(hash_table_t *tblctx, void *key, void *val)
{
    if (tblctx->arrused > MULT_FRAC(tblctx->arrsz, 3, 4))
    {
        newctx = hash_table_create(MULT_FRAC(tblctx->arrsz, 3, 2));
    }

    uint64_t hash = __hash_cstring((char*)key);
    uint64_t insert = hash % tblctx->arrsz;
}
