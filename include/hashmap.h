/// Hashmap header file
/// @author altair
/// @version 0.0.1
///

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string.h>
#include <stdlib.h>

typedef struct _node_t {
    void *data;
    struct _node_t *next_node;
} node_t;

node_t *create_linked_list();
node_t *_create_node(void *data);
void _pushback_node(node_t **head, void *data);
void delete_linked_list(node_t **head);

typedef struct {
    node_t *linked_list;
    size_t length;
} bucket_t;

bucket_t *create_bucket();
void pushback(bucket_t *bucket, void *data);
void *get_from_bucket(bucket_t *bucket, size_t index);
void delete_bucket(bucket_t *bucket);

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
} hashmap_t;

hashmap_t *create_hashmap();

#endif // HASH_MAP_H
