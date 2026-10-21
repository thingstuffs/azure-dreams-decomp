#include "common.h"
#include "m2c_compat.h"

extern s32 dungeon_menu_object;

typedef struct S_800DBF38_0 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800DBF38_0;

/* Clears bit 0 of the flags in the current state record. */
void clear_state_flag_bit(void) {
    S_800DBF38_0 *state;

    state = dungeon_menu_object + 0x20;
    state->unk_54 = (s32) (state->unk_54 & ~1);
}
