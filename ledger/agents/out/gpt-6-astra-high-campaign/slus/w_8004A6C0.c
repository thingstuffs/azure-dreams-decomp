#include "common.h"

struct Entry { short a; short b; };
extern struct Entry D_80013564[];
/* Returns the index of the first matching value pair, or 20 if none matches. */
int func_8004A6C0(int first_value, int second_value) {
    int entry_index = 0;
    struct Entry *entry = D_80013564;
    for (; entry_index < 20; entry_index++, entry++) {
        if (entry->a == first_value && entry->b == second_value) break;
    }
    return entry_index;
}
