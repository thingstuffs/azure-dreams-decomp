#include "common.h"

#include "common.h"

typedef struct {
    s16 key;
    s16 value;
} Entry;

extern Entry D_8006A94C[];
extern void func_80033AA8(s32 arg0);

/* Pass each matching key's value to func_80033AA8. */
void func_80035D4C(s16 key) {
    Entry *entry = D_8006A94C;

    if (entry->key != 0) {
        do {
            if (key == entry->key) {
                func_80033AA8(entry->value);
            }
            entry++;
        } while (entry->key != 0);
    }
}
