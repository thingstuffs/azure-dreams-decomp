#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_801237A4();    /* extern */
typedef struct HalfValue {
    s32 pad[2];
    u16 value;
} HalfValue;

typedef struct ValueLink {
    s32 pad;
    HalfValue *next;
} ValueLink;

extern s32 * volatile D_80129728[28];

typedef struct S_801237E8_0 {
    u8 pad_00[0x16];
    u8 unk_16;
} S_801237E8_0;   /* arg0 in func_801237E8 */

/* Swap paired slot values and linked halfwords, toggle the state flag, and update. */
void func_801237E8(S_801237E8_0 *state) {
    s32 * volatile *slots;
    s32 * volatile *right_slot;
    s32 * volatile *left_slot;
    s32 *left_word;
    s32 saved_word;
    s32 slot_index;
    u16 saved_half;
    ValueLink *right;
    ValueLink *left;
    HalfValue *right_value;
    HalfValue *left_value;

    slot_index = 2;
    slots = D_80129728;
    right_slot = slots + 0x10;
    left_slot = slots + 2;
    do {
        left_word = *left_slot;
        left_slot += 1;
        saved_word = *left_word;
        slot_index += 1;
        *left_word = **right_slot;
        **right_slot = saved_word;
        right_slot += 1;
    } while (slot_index < 0xE);
    right = (ValueLink *) D_80129728[22];
    left = (ValueLink *) D_80129728[8];
    right_value = right->next;
    left_value = left->next;
    saved_half = left_value->value;
    left_value->value = right_value->value;
    ((ValueLink *) D_80129728[22])->next->value = saved_half;
    state->unk_16 = (s8) (state->unk_16 ^ 1);
    func_801237A4(state, saved_half, left_slot, slot_index);
}
