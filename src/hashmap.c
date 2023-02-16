#include <hashmap.h>

node_t *create_linked_list() {
    node_t *head = NULL;
    return head;
}

node_t *_create_node(void *data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next_node = NULL;
    return new_node;
}

void pushback_node(node_t **head, void *data) {
    // If linked list is empty,
    if (*head == NULL) {
    *head = _create_node(data);
    }
    // or, if linked list is not empty.
    else {
    node_t *cur = *head;
    while (cur->next_node != NULL) {
        cur = cur->next_node;
    }
    node_t *new_tail = _create_node(data);
    cur->next_node = new_tail;
    }
}

void delete_linked_list(node_t **head) {
    if (*head == NULL) {
    return;
    }
    node_t *cur = *head;
    do {
    node_t *next = cur->next_node;
    cur->next_node = NULL;
    free(cur);
    cur = next;
    } while (cur != NULL); 
    *head = NULL;
}

bucket_t *create_bucket() {
    bucket_t *new_bucket = (bucket_t *)malloc(sizeof(bucket_t));
    new_bucket->linked_list = create_linked_list();
    new_bucket->length = 0;
    return new_bucket;
}

void pushback(bucket_t *bucket, void *data) {
    pushback_node(&bucket->linked_list, data);
    bucket->length++;
}

void *get_from_bucket(bucket_t *bucket, size_t index) {
    if (bucket == NULL || index >= bucket->length) {
    return NULL;
    }
    node_t *cur = bucket->linked_list;
    for (int i = 0; i < index; i++) {
    if (cur->next_node == NULL) {
        return NULL;
    } 
    else {
        cur = cur->next_node;
    }
    }
    return cur->data;
}

void delete_bucket(bucket_t *bucket) {
   if (bucket == NULL){
      return;
   }
   delete_linked_list(&bucket->linked_list);
   bucket->length = 0;
}

void print_bucket(bucket_t *bucket) {
    if (bucket->length == 0) {
        printf("NULL\n");
    } else {
        printf("length: %d\n", bucket->length);
    }
}

hashmap_t *create_hashmap(uint8_t *(*hash_func)(void *)) {
    hashmap_t *hashmap = (hashmap_t *)malloc(sizeof(hashmap_t));
    hashmap->bucket_list = (bucket_t **)malloc(sizeof(bucket_t*) * DEFAULT_BUCKET_COUNT);
    hashmap->length = DEFAULT_BUCKET_COUNT;
    for (int i = 0; i < hashmap->length; i++) {
        hashmap->bucket_list[i] = create_bucket();
    }
    hashmap->hash_func = hash_func;
    return hashmap;
}

void put(hashmap_t *hashmap, void *key, void *value) {
    uint8_t *digest = hashmap->hash_func(key);
#ifdef HASH_SIZE
    size_t digest_size = HASH_SIZE;
#else
    // Minimum size of the digest. 
    // For the most efficient value from hashing, 
    // such as avoiding collision, evenly distributing,
    // Or, when the size of hash digest is smaller than default,
    // define HASH_SIZE value with size of hash digest.
    size_t digest_size = 8;
#endif
    unsigned int start_ptr = 0;
    if (digest_size < 16) {
        start_ptr = 0;
    } else {
        start_ptr = digest_size - 16;
    }
    size_t index = arr_to_uint(digest + start_ptr, digest_size - start_ptr) % hashmap->length;
    pushback(hashmap->bucket_list[index], value);
    printf("%d\n", index);
}

uint64_t arr_to_uint(uint8_t *arr, size_t length) {
    uint64_t summary = 0;
    for (int i = 0; i < length; i++) {
        summary += (arr[i] << (i));
    }
    return summary;
}

void print_all_bucket(hashmap_t *hashmap) {
    printf("hashmap size: %d\n", hashmap->length);
    for (size_t i = 0; i < hashmap->length; i++) {
        printf("%d - ", i);
        print_bucket(hashmap->bucket_list[i]);
    }
}
