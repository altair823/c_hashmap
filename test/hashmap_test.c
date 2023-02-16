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

uint8_t *test_func(void *key) {
    uint8_t *test_key = (uint8_t *)malloc(sizeof(uint8_t) * 32);
    for (int i = 0; i < 32; i++) {
        test_key[i] = 13;
    }
    return test_key;
}

void index_from_hash_test() {
    INIT_TEST_SUITE;
    size_t digest_size = 32;
    uint8_t arr[digest_size];
    for (int i = 0; i < digest_size; i++) {
        arr[i] = 0x1;
    }
       unsigned int start_ptr = 0;
    if (digest_size < 16) {
        start_ptr = 0;
    } else {
        start_ptr = digest_size - 16;
    }
    uint64_t summary = arr_to_uint(arr + start_ptr, digest_size - start_ptr);
    assert(summary == 0xffff);
    END_TEST_SUITE;
}

void hashmap_test() {
    INIT_TEST_SUITE;
    hashmap_t *hashmap = create_hashmap(test_func);
    assert(hashmap->length == DEFAULT_BUCKET_COUNT);
    assert(hashmap->hash_func == test_func);
    uint8_t key[8] = {0, };
    uint8_t value[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    put(hashmap, key, value);
    put(hashmap, key, value);
    print_all_bucket(hashmap);
    END_TEST_SUITE;
}

int main() {
    linked_list_test();
    bucket_test();
    index_from_hash_test();
    hashmap_test();
}
