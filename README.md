# Hashmap Implementation written in C

Hashmap implementation using vim in arch linux terminal.

## Requirement

To use hashmap, must provide hash function and comparator for keys. 
The hash function sould return pointer of integers(bytes-unsigned chars are preferred) that is fixed its length. 
You must define the length of the hash digest in hashmap.h header file to summary the digest to index of hashmap. 

And the comparator must return 0 when keys are the same. 


## Build and Test

- Build

```bash
mkdir build && cd build
cmake ..
make
```

- Test
```bash
cd build
ctest -V
```

