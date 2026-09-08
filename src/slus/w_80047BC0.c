#include "common.h"

/* struct element of D_80083D08: only the s16 field at offset 6 is read by this function */
typedef struct {
    u8 unk0[6];
    s16 unk6;
} S_80047BC0;

extern S_80047BC0 D_80083D08[6];

/* Returns the first slot index with the requested ID in D_80083D08, or -1 if absent. */
s32 func_80047BC0(s32 slot_id) {
    S_80047BC0 *slot;
    s32 match_index = -1;
    s32 slot_index = 0;
    slot = D_80083D08;

    for (; slot_index < 6; slot_index++, slot++) {
        if (slot->unk6 == slot_id) {
            match_index = slot_index;
            break;
        }
    }
    return match_index;
}
