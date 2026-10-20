#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* Increment three dungeon state bytes by two, or set flags when the first reaches 0x80. */
s32 brighten_encounter_view_color(u16 *dataCursor)
{
    u8 firstStateByte = g_game_work.view.tint.parts.tint_r;


    if (firstStateByte < 0x80U) {
        g_game_work.view.tint.parts.tint_r = firstStateByte + 2;
        g_game_work.view.tint.parts.tint_g += 2;
        g_game_work.view.tint.parts.tint_b += 2;
        return;
    }

    dataCursor[-1] |= 0x8000;
    return object_flag_block.flags |= 0x8000;
}
