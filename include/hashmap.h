/// Hashmap header file
/// @author altair
/// @version 0.0.1
///

#ifndef HASH_MAP_H
#define HASH_MAP_H

#define DEBUG 0

#include <stdlib.h>
#include <stdint.h>

#if DEBUG == 1
#include <stdio.h>
#endif

typedef struct _node_t {
    void *key;
    void *value;
    struct _node_t *next_node;
} node_t;

node_t *create_linked_list();
node_t *create_node(void *key, void *value);
void pushback_node(node_t **head, node_t *node);
void delete_linked_list(node_t **head);

typedef struct {
    node_t *linked_list;
    size_t length;
} bucket_t;

bucket_t *create_bucket();
void pushback(bucket_t *bucket, void *key, void *value);
node_t *get_from_bucket(bucket_t *bucket, size_t index);
void *find_from_bucket(bucket_t *bucket, int (*cmp_key_func)(void *, void *), void *key);
void delete_bucket(bucket_t *bucket);

#if DEBUG == 1
void print_bucket(bucket_t *bucket);
#endif

#define DEFAULT_BUCKET_COUNT 32

/**
 * @brief Hashmap struct.
 * @detail Hashmap struct implementing with linked-list-based bucket list.
 * Default length of bucket list is defined in DEFAULT_BUCKET_COUNT(hashmap.h).
 * When the biggest bucket size exceeds specific threshold defined, 
 * bucket list will be reallocated double. 
 * Detail implementation and optimization can be different across versions. 
 */
typedef struct {
    bucket_t **bucket_list;
    size_t length;
    uint8_t *(*hash_func)(void *);
    int (*cmp_key)(void *, void *);
} hashmap_t;

hashmap_t *create_hashmap(uint8_t *(*hash_func)(void *), int (*cmp_key)(void *, void *));
void put(hashmap_t *hashmap, void *key, void *value);
void *get(hashmap_t *hashmap, void *key);

#define MAX_DIGEST_LEN_TO_USE 16
size_t reduce_hash(uint8_t *digest, size_t length);
uint64_t arr_to_uint(uint8_t *arr, size_t length);

#if DEBUG == 1
void print_all_bucket(hashmap_t *hashmap);
#endif

#endif // HASH_MAP_H
