#include "modules/dungeon_dungeon_setup.h"

void apply_state_index_tile_masks(void)
{
    void *state = ((u8 *)(&g_game_work));

    state = (u8 *)state + 0x1DC;

    apply_tile_flags_to_rectangle(0, 0, (s16)(1 << *(s16 *)((u8 *)state + 0x14)),
                  (s16)(1 << *(s16 *)((u8 *)state + 0x16)));
}

/* MECHANISM: Keep the natural 24-byte call frame with only $ra saved at 0x10.
   Split D_80083160 address formation from the +0x1DC adjustment to retain
   retail's lui/addiu/addiu sequence without an ASM_KEEP scheduling fence. */
