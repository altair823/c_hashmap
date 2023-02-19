#include <assert.h>
#include "test_util.h"

#include "hashmap.h"

void linked_list_test() {
    INIT_TEST_SUITE;
    node_t *head = create_linked_list();
    assert(head == NULL);
    // pushback test
    int a = 49;
    node_t *node1 = create_node((void *)&a, (void *)&a);
    pushback_node(&head, node1);
    assert(*(int *)head->key == 49);
    assert(*(int *)head->value == 49);
    char *b = (char *)malloc(sizeof(char));
    *b = 93;
    node_t *node2 = create_node((void *)b, (void *)b);
    pushback_node(&head, node2);
    assert(*(char *)head->next_node->key == 93);
    assert(*(char *)head->next_node->value == 93);
    
    // delete test
    delete_linked_list(&head);
    assert(head == NULL);
    free(b);
    END_TEST_SUITE;
}
    
void bucket_test() {
    INIT_TEST_SUITE;
    bucket_t *bucket = create_bucket();
    assert(bucket->length == 0);
    // pushback test
    int a = 49;
    pushback(bucket, (void *)&a, (void *)&a);
    assert(*(int *)bucket->linked_list->key == 49);
    assert(*(int *)bucket->linked_list->value == 49);
    assert(*(int *)get_from_bucket(bucket, 0)->key == 49);
    assert(*(int *)get_from_bucket(bucket, 0)->value == 49);
    assert(bucket->length == 1);
    char *b = (char *)malloc(sizeof(char));
    *b = 93;
    pushback(bucket, (void *)b, (void *)b);
    assert(*(char *)bucket->linked_list->next_node->key == 93);
    assert(*(char *)bucket->linked_list->next_node->value == 93);
    assert(*(char *)get_from_bucket(bucket, 1)->key == 93);
    assert(*(char *)get_from_bucket(bucket, 1)->value == 93);
    assert(bucket->length == 2);
    struct c_t {
        int i;
        double j;
    };
    struct c_t *c = (struct c_t *)malloc(sizeof(struct c_t));
    c->i = 36;
    c->j = 82.65;
    pushback(bucket, (void *)c, (void *)c);
    assert(((struct c_t *)get_from_bucket(bucket, 2)->key)->i == 36);
    assert(((struct c_t *)get_from_bucket(bucket, 2)->key)->j == 82.65);
    assert(((struct c_t *)get_from_bucket(bucket, 2)->value)->i == 36);
    assert(((struct c_t *)get_from_bucket(bucket, 2)->value)->j == 82.65);
 
    assert(bucket->length == 3);

    // delete test
    delete_bucket(bucket);
    assert(bucket->linked_list == NULL);
    assert(bucket->length == 0);
    free(b);
    free(c);
    END_TEST_SUITE;
}

uint8_t *test_func(void *key) {
    uint8_t *test_key = (uint8_t *)malloc(sizeof(uint8_t) * 32);
    for (int i = 0; i < 32; i++) {
        test_key[i] = 13;
    }
    return test_key;
}

int test_cmp(void *key1, void *key2) {
    uint8_t *t_key1 = (uint8_t *)key1;
    uint8_t *t_key2 = (uint8_t *)key2;
    for (int i = 0; i < 32; i++) {
        if (t_key1[i] < t_key2[i]) {
            return -1;
        } else if (t_key1[i] > t_key2[i]) {
            return 1;
        }
    }
    return 0;
}

void index_from_hash_test() {
    INIT_TEST_SUITE;
    size_t digest_size = 32;
    uint8_t arr[digest_size];
    for (int i = 0; i < digest_size; i++) {
        arr[i] = 0x1;
    }
    size_t summary = reduce_hash(arr, digest_size);
    assert(summary == 0xffff);
    END_TEST_SUITE;
}

void hashmap_test() {
    INIT_TEST_SUITE;
    hashmap_t *hashmap = create_hashmap(test_func, test_cmp);
    assert(hashmap->length == DEFAULT_BUCKET_COUNT);
    assert(hashmap->hash_func == test_func);
    uint8_t key[8] = {0, };
    uint8_t value[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    put(hashmap, key, value);
    size_t expected_index = reduce_hash(test_func(key), 32) % hashmap->length;
    assert(hashmap->bucket_list[expected_index] != NULL);
    uint8_t *v = (uint8_t *)get(hashmap, key);
    for (int i = 0; i < 8; i++) {
        assert(value[i] == v[i]);
    }
    END_TEST_SUITE;
}

int main() {
    linked_list_test();
    bucket_test();
    index_from_hash_test();
    hashmap_test();
}
