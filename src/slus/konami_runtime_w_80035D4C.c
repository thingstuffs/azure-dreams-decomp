#include "common.h"

#include "common.h"

typedef struct {
    s16 key;
    s16 value;
} Entry;

extern Entry D_8006A94C[];
extern void setResidentBitmapBit(s32 bit_id);

/* Pass each matching key's value to setResidentBitmapBit. */
void func_80035D4C(s16 key) {
    Entry *entry = D_8006A94C;

    if (entry->key != 0) {
        do {
            if (key == entry->key) {
                setResidentBitmapBit(entry->value);
            }
            entry++;
        } while (entry->key != 0);
    }
}
