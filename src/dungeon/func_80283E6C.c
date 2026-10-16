#include "modules/dungeon_dungeon_setup.h"

void dungeonApplyStateIndexTileMasks(void)
{
    void *state = ((u8 *)(&gameWork));

    state = (u8 *)state + 0x1DC;

    dungeonApplyTileFlagsToRectangle(0, 0, (s16)(1 << *(s16 *)((u8 *)state + 0x14)),
                  (s16)(1 << *(s16 *)((u8 *)state + 0x16)));
}

/* MECHANISM: Keep the natural 24-byte call frame with only $ra saved at 0x10.
   Split D_80083160 address formation from the +0x1DC adjustment to retain
   retail's lui/addiu/addiu sequence without an ASM_KEEP scheduling fence. */
