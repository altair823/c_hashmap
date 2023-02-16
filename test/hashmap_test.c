#include <assert.h>
#include "test_util.h"

#include "hashmap.h"

void linked_list_test() {
	INIT_TEST_SUITE;
	node_t *head = create_linked_list();
	assert(head == NULL);
	// pushback test
	int a = 49;
	pushback_node(&head, (void *)&a);
	assert(*(int *)head->data == 49);
	char *b = (char *)malloc(sizeof(char));
	*b = 93;
	pushback_node(&head, b);
	assert(*(char *)head->next_node->data == 93);
	
	// delete test
	delete_linked_list(&head);
	assert(head == NULL);
	END_TEST_SUITE;
}
	
void bucket_test() {
	INIT_TEST_SUITE;
	bucket_t *bucket = create_bucket();
	assert(bucket->length == 0);
	// pushback test
	int a = 49;
	pushback(bucket, (void *)&a);
	assert(*(int *)bucket->linked_list->data == 49);
	assert(*(int *)get_from_bucket(bucket, 0) == 49);
	assert(bucket->length == 1);
	char *b = (char *)malloc(sizeof(char));
	*b = 93;
	pushback(bucket, (void *)b);
	assert(*(char *)bucket->linked_list->next_node->data == 93);
	assert(*(char *)get_from_bucket(bucket, 1) == 93);
	assert(bucket->length == 2);
	struct c_t {
		int i;
		double j;
	};
	struct c_t *c = (struct c_t *)malloc(sizeof(struct c_t));
	c->i = 36;
	c->j = 82.65;
	pushback(bucket, (void *)c);
	assert(((struct c_t *)get_from_bucket(bucket, 2))->i == 36);
	assert(((struct c_t *)get_from_bucket(bucket, 2))->j == 82.65);
	assert(bucket->length == 3);

	// delete test
	delete_bucket(bucket);
	assert(bucket->linked_list == NULL);
	assert(bucket->length == 0);
	END_TEST_SUITE;
}

int main() {
	linked_list_test();
	bucket_test();
}
