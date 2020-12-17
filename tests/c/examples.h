
#ifndef MULTIHASH_EXAMPLES_H
#define MULTIHASH_EXAMPLES_H

#include <stddef.h>

char sha1_example[] = {
        17, 20, 124, 131, 87, 87, 127, 81, 212, 240, 168, 211, 147, 170, 26, 170, 251, 40, 134, 61, 148, 33
};

size_t sha1_example_length = sizeof(sha1_example);

char sha2_example[] = {
        18, 32, 144, 234, 104, 142, 39, 93, 88, 5, 103, 50, 80, 50, 73, 43, 89, 123, 199, 114, 33, 198, 36, 147, 231, 99, 48, 184, 93, 221, 161, 145, 239, 124
};

size_t sha2_example_length = sizeof(sha2_example);

char sha3_example[] = {
        20, 64, 250, 226, 201, 235, 25, 144, 96, 87, 248, 191, 80, 127, 14, 115, 238, 2, 187, 102, 157, 88, 195, 6, 158, 119, 24, 184, 156, 164, 211, 20, 207, 79, 214, 241, 103, 144, 25, 204, 70, 209, 133, 199, 175, 52, 246, 192, 90, 48, 123, 7, 14, 116, 233, 237, 91, 156, 100, 248, 106, 172, 194, 185, 13, 16
};

size_t sha3_example_length = sizeof(sha3_example);

#endif //MULTIHASH_EXAMPLES_H
