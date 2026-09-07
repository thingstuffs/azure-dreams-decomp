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

void func_80123130(void) {
    s16 i;

    D_80129724 = 0;
    D_80129720 = D_80129620;
    for (i = 0; i < 32; i++) {
        if (i != 31) {
            D_80129620[i].next = &D_80129620[i + 1];
        } else {
            D_80129620[i].next = 0;
        }
        D_80129620[i].value = i * 48;
        D_80129620[i].state = 0;
    }
    func_80041110(D_80123124);
}

/* MECHANISM: A natural s16 induction variable over an eight-byte record array
   exposes the held base/base+8 pair and post-increment comparison seen in retail.
   The sole post-loop call produces the 24-byte frame with only the ra save. */
