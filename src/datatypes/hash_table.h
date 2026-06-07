#ifndef DATATYPES_HASHTABLE_H_
#define DATATYPES_HASHTABLE_H_

#include <datatypes/len_data.h>

#include <stdint.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE sizeof(hash_table_t)
#define HASH_TABLE_COLLISION_SIZE_HINT 100

typedef struct {
    size_t arrsz;
    size_t arrused;
    void **arr;

	// For resolving collisions
	hash_table_t *colls;
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
  - len_data_t *key: the key to use for insertion.
  - len_data_t *val: the value to insert into the table.

  Returns:
  (void)

  Remarks:
  - Note that it may rehash the table if necessary.
  - It will automatically handle collisions, but IS NOT SAFE if the key is already present.
*/
void hash_table_insert(hash_table_t*, len_data_t*, len_data_t*)

#endif
