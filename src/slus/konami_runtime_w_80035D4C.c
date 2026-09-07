#include "common.h"

#include "common.h"

typedef struct {
    s16 key;
    s16 value;
} Entry;

extern Entry D_8006A94C[];
extern void func_80033AA8(s32 arg0);

void func_80035D4C(s16 arg0) {
    Entry *entry = D_8006A94C;

    if (entry->key != 0) {
        do {
            if (arg0 == entry->key) {
                func_80033AA8(entry->value);
            }
            entry++;
        } while (entry->key != 0);
    }
}
