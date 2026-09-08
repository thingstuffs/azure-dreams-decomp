#include "common.h"

typedef struct Entry Entry;

struct Entry {
    Entry *next;
    s16 value;
    s16 state;
};

extern u8 D_80123124[];
extern Entry D_80129620[32];
extern Entry *D_80129720;
extern s16 D_80129724;

extern void func_80041110(void *);

/* Initializes the entry list with cleared states and values spaced by 48. */
void func_80123130(void) {
    s16 entry_index;

    D_80129724 = 0;
    D_80129720 = D_80129620;
    for (entry_index = 0; entry_index < 32; entry_index++) {
        if (entry_index != 31) {
            D_80129620[entry_index].next = &D_80129620[entry_index + 1];
        } else {
            D_80129620[entry_index].next = 0;
        }
        D_80129620[entry_index].value = entry_index * 48;
        D_80129620[entry_index].state = 0;
    }
    func_80041110(D_80123124);
}
