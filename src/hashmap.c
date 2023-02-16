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

hashmap_t *create_hashmap() {
    hashmap_t *hashmap = (hashmap_t *)malloc(sizeof(hashmap_t));
    hashmap->bucket_list = (bucket_t **)malloc(sizeof(bucket_t*) * DEFAULT_BUCKET_COUNT);
    hashmap->length = DEFAULT_BUCKET_COUNT;
    for (int i = 0; i < hashmap->length; i++) {
	hashmap->bucket_list[i] = create_bucket();
    }
    return hashmap;
}
