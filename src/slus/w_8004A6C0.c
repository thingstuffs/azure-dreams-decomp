#include "common.h"

struct Entry { short a; short b; };
/* Returns the index of the first matching value pair, or 20 if none matches. */
int func_8004A6C0(int first_value, int second_value) {
    int entry_index;
    for (entry_index = 0; entry_index < 20; entry_index++) {
        s32 offset = entry_index * sizeof(struct Entry);
        if (((struct Entry *)(offset + 0x80013564))->a == first_value
            && ((struct Entry *)(offset + 0x80013564))->b == second_value)
            break;
    }
    return entry_index;
}
