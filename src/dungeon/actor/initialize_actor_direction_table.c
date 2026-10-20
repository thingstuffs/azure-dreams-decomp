#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern void func_8003DB94(void *, s32, s32);
extern u8 D_800E260C[];

// Initialize object state and apply a table entry selected by the adjusted heading.
void initialize_actor_direction_table(void *object, void *unusedContext, void *tableTarget, void *headingSource) {
    s32 tableByteOffset;

    *((u8 *)object + 0x9A) = 0x10;
    *((u8 *)object + 0x9B) = 0;
    ((SpriteFrameState *)tableTarget)->frameTable = D_800E260C;
    tableByteOffset = ((g_game_work.view.viewAngle + *(s16 *)((u8 *)headingSource + 0x2A) + 0x100) >> 7) & 0x1C;
    func_8003DB94(tableTarget, *(s32 *)(D_800E260C + tableByteOffset), 0);
}
