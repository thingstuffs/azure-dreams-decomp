#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increments three state bytes while the first is below 0x80, otherwise sets flag bits. */
s32 advance_three_state_bytes(u16 *words)
{
    u8 state_value = g_game_work.view.tint.parts.tint_r;

    if (state_value < 0x80U) {
        g_game_work.view.tint.parts.tint_r = state_value + 4;
        g_game_work.view.tint.parts.tint_g += 4;
        g_game_work.view.tint.parts.tint_b += 4;
        return;
    }

    words[-1] |= 0x8000;
    return object_flag_block.flags |= 0x8000;
}
