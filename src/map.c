#include <map.h>

node_t *create_linked_list() {
    node_t *head = NULL;
    return head;
}

node_t *create_node(void *data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next_node = NULL;
    return new_node;
}

void pushback_node(node_t *head, void *data) {
    // If linked list is empty,
    if (head == NULL) {
	head = create_node(data);
    }
    // or, if linked list is not empty.
    else {
	node_t *cur = head;
	while (cur->next_node != NULL) {
	    cur = cur->next_node;
	}
	node_t *new_tail = create_node(data);
	cur->next_node = new_tail;
    }
}


bucket_t *create_bucket() {
    bucket_t *new_bucket = (bucket_t *)malloc(sizeof(bucket_t));
    new_bucket->linked_list = create_linked_list();
    new_bucket->length = 0;
    return new_bucket;
}
