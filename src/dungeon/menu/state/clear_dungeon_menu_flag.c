#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu/state.h"
#include "dungeon/data.h"


typedef struct S_800DBF38_0 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800DBF38_0;

/* Clears bit 0 of the flags in the current state record. */
void clear_dungeon_menu_flag(void) {
    S_800DBF38_0 *state;

    state = NODE_BODY(dungeon_menu_object);
    state->unk_54 = (s32) (state->unk_54 & ~1);
}
