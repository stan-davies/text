#ifndef STR_H
#define STR_H

#include <stddef.h>     // For `size_t`.

/*
 *      Basic, safer string with start and end pointers and a length.
 */
struct str {
        char           *beg     ;       // Data begin.
        char           *end     ;       // Data end - on the null terminator.
        size_t          len     ;       // Length of data.
};

struct str create_str(
        void
);

void dest_str(
        struct str             *s
);

/*
 * Alters the length of the given string, altering each datum accordingly -
 * note that the end pointer is placed at the same offset from the start, but
 * in the new memory block.
 * Returns success.
 */
int resize_str(
        struct str             *s       ,
        int                     r
);

#endif
