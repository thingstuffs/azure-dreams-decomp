#include "common.h"

typedef struct {
    u8 pad[0xBBC];
    s16 values[1];
} InputTable;

typedef struct {
    s32 words[12];
    s32 flags;
} State;

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern InputTable devkit_globals_page;
extern State *devkit_state_slots[3];
extern CallbackOwner *devkit_callback_owner[4];

extern s32 func_80700D84(s32 index, s32 input_a, s32 input_b, s32 input_c);
extern s32 func_80701060(s32 *word, s32 old_value);

/* Sets a selected bitmap bit for accepted input, or updates flag 0x40000000 from the status callback. */
s32 update_selection_mask_and_status(s32 index, s32 input_a, s32 input_b, s32 input_c) {
    s32 old_value;
    s32 shift;
    s32 *word;

    if (func_80700D84(index, input_a, input_b, input_c) >= 2) {
        old_value = devkit_globals_page.values[index];
        word = &devkit_state_slots[0]->words[old_value / 32];
        shift = old_value % 32;
        old_value = *word;
        *word = (1 << shift) | old_value;
        return func_80701060(word, old_value);
    }
    if (devkit_callback_owner[0]->callback(2) != 0) {
        devkit_state_slots[0]->flags |= 0x40000000;
    } else {
        devkit_state_slots[0]->flags &= ~0x40000000;
    }
    return index;
}
