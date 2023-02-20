#include <hashmap.h>

node_t *create_linked_list() {
    node_t *head = NULL;
    return head;
}

node_t *create_node(void *key, void *value) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next_node = NULL;
    return new_node;
}

void pushback_node(node_t **head, node_t *node) {
    // If linked list is empty,
    if (*head == NULL) {
        *head = node;
    }
    // or, if linked list is not empty.
    else {
        node_t *cur = *head;
    while (cur->next_node != NULL) {
        cur = cur->next_node;
    }
    node_t *new_tail = node;
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

void pushback(bucket_t *bucket, void *key, void *value) {
    node_t *node = create_node(key, value);
    pushback_node(&bucket->linked_list, node);
    bucket->length++;
}

node_t *get_from_bucket(bucket_t *bucket, size_t index) {
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
    return cur;
}

void *find_from_bucket(bucket_t *bucket, int (*cmp_key_func)(void *, void *), void *key) {
    if (bucket == NULL || key == NULL) {
        return NULL;
    }
    node_t *cur = bucket->linked_list;
    while(1) {
        if (cmp_key_func(key, cur->key) == 0){
            return cur->value;
        }
        if (cur->next_node == NULL) {
            return NULL;
        }
        cur = cur->next_node;
    }
}

void delete_bucket(bucket_t *bucket) {
   if (bucket == NULL){
      return;
   }
   delete_linked_list(&bucket->linked_list);
   bucket->length = 0;
}

#if DEBUG == 1
void print_bucket(bucket_t *bucket) {
    if (bucket->length == 0) {
        printf("NULL\n");
    } else {
        printf("length: %d\n", bucket->length);
    }
}
#endif

hashmap_t *create_hashmap(uint8_t *(*hash_func)(void *), int (*cmp_key)(void *, void *)) {
    hashmap_t *hashmap = (hashmap_t *)malloc(sizeof(hashmap_t));
    hashmap->bucket_list = (bucket_t **)malloc(sizeof(bucket_t*) * DEFAULT_BUCKET_COUNT);
    hashmap->length = DEFAULT_BUCKET_COUNT;
    for (int i = 0; i < hashmap->length; i++) {
        hashmap->bucket_list[i] = create_bucket();
    }
    hashmap->hash_func = hash_func;
    hashmap->cmp_key = cmp_key;
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
    size_t index = reduce_hash(digest, digest_size) % hashmap->length;
    pushback(hashmap->bucket_list[index], key, value);
}

size_t reduce_hash(uint8_t *digest, size_t length) {
    unsigned int start_ptr = 0;
    if (length < MAX_DIGEST_LEN_TO_USE) {
        start_ptr = 0;
    } else {
        start_ptr = length - 16;
    }
    return arr_to_uint(digest + start_ptr, length - start_ptr);
}

uint64_t arr_to_uint(uint8_t *arr, size_t length) {
    uint64_t summary = 0;
    for (int i = 0; i < length; i++) {
        summary += (arr[i] << (i));
    }
    return summary;
}

void *get(hashmap_t *hashmap, void *key) {
#ifdef HASH_SIZE
    size_t digest_size = HASH_SIZE;
#else
    size_t digest_size = 8;
#endif
    size_t index = reduce_hash(hashmap->hash_func(key), digest_size) % hashmap->length;
    if (hashmap->bucket_list[index] == NULL) {
        return NULL;
    }
    return find_from_bucket(hashmap->bucket_list[index], hashmap->cmp_key, key);
}

#if DEBUG == 1
void print_all_bucket(hashmap_t *hashmap) {
    printf("hashmap size: %d\n", hashmap->length);
    for (size_t i = 0; i < hashmap->length; i++) {
        printf("%d - ", i);
        print_bucket(hashmap->bucket_list[i]);
    }
}
#endif
