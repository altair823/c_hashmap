#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define HASH_SIZE 32

typedef struct {
    uint8_t hash_v[HASH_SIZE];
} digest_t;

bool init_digest(digest_t *digest);

#endif // HASH_H
