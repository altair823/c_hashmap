#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node_t {
    void *data;
    struct _node_t *next_node;
} node_t;

node_t *create_linked_list();
node_t *create_node(void *data);
void pushback_node(node_t *head, void *data);


typedef struct {
    node_t *linked_list;
    size_t length;
} bucket_t;

bucket_t *create_bucket();
bool pushback(bucket_t *bucket);
