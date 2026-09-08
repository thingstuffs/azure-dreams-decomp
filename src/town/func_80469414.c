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

/* Select the next entry whose value passes func_8001E670, wrapping at the terminator. */
u8 func_8001A414(void) {
    s32 start_index;
    s32 next_index;
    u8 *entry_id;

    start_index = D_8001E950->index;
    next_index = start_index + 1;
    if (next_index != start_index) {
        Entry *entries = D_8001791C;
        u8 *entry_ids = D_80017BB0;

        entry_id = &entry_ids[next_index];
        do {
            if (*entry_id == 0) {
                entry_id = entry_ids;
                next_index = 0;
            }
            if (func_8001E670(entries[*entry_id].value) != 0) {
                break;
            }
            next_index++;
            entry_id++;
        } while (next_index != start_index);
    }
    D_8001E950->index = next_index;
    return D_80017BB0[next_index];
}
