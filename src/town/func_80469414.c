#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 value;
    u8 pad6[6];
} Entry;

typedef struct {
    u8 pad0[2];
    s8 index;
} State;

extern s32 func_8001E670(s32 value);
extern Entry D_8001791C[];
extern u8 D_80017BB0[];
extern State *D_8001E950;

u8 func_8001A414(void) {
    s32 original;
    s32 index;
    u8 *cursor;

    original = D_8001E950->index;
    index = original + 1;
    if (index != original) {
        Entry *entries = D_8001791C;
        u8 *values = D_80017BB0;

        cursor = &values[index];
        do {
            if (*cursor == 0) {
                cursor = values;
                index = 0;
            }
            if (func_8001E670(entries[*cursor].value) != 0) {
                break;
            }
            index++;
            cursor++;
        } while (index != original);
    }
    D_8001E950->index = index;
    return D_80017BB0[index];
}
