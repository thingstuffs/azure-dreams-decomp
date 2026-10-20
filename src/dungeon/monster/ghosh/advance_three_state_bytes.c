#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increments three state bytes while the first is below 0x80, otherwise sets flag bits. */
s32 advance_three_state_bytes(u16 *words)
{
    u8 state_value = g_game_work.view.unk_090;

    if (state_value < 0x80U) {
        g_game_work.view.unk_090 = state_value + 4;
        g_game_work.view.unk_091 += 4;
        g_game_work.view.unk_092 += 4;
        return;
    }

    words[-1] |= 0x8000;
    return object_flag_block.flags |= 0x8000;
}
