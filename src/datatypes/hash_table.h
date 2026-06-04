#ifndef DATATYPES_HASHTABLE_H_
#define DATATYPES_HASHTABLE_H_

#include <stdint.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE sizeof(hash_table_t)

typedef struct {
    size_t arrsz;
    size_t arrused;
    void **arr;
} hash_table_t;

/*
 * Creates a hash table.
 * Parameters:
 * - size_t size_hint: the minimum size of table to try and create
 *
 * Returns:
 * (hash_table_t *) The returned hash table, or NULL if failed.
*/
hash_table_t *hash_table_create(size_t);

/*
  Frees a hash table.
  Parameters:
  - hash_table_t *tctx: the table to destroy.

  Returns:
  (void)

  Remarks:
  - Note that it DOES NOT free the contents of the hash table, only the array pointing to said contents.
*/
void hash_table_destroy(hash_table_t*);

/*
  Inserts a new key/value pair into a hash table.
  Parameters:
  - hash_table_t *tblctx: the table to insert into.
  - void *key: the key to use for insertion.
  - void *val: the value to insert into the table.

  Returns:
  (void)

  Remarks:
  - Note that it may rehash the table if necessary.
  - It will automatically handle collisions.
*/

#endif
