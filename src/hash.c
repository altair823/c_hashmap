#include <hash.h>

bool init_digest(digest_t *digest) {
    if (!digest){
	return false;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
	digest->hash_v[i] = 0;
    }
    return true;
}


