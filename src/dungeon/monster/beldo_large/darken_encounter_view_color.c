#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"


/* Decrease three state bytes, or set entry and global flags below the threshold. */
void darken_encounter_view_color(u16 *entry)
{

    if (g_game_work.view.tint.parts.tint_r >= 0x3D) {
        g_game_work.view.tint.parts.tint_r -= 2;
        g_game_work.view.tint.parts.tint_g -= 2;
        g_game_work.view.tint.parts.tint_b -= 2;
        return;
    }

    entry[-1] |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
