#include "modules/dungeon_resource10_slot0.h"

void func_80174670(void *node, s32 tile_x, s32 tile_y, s16 target_height)
{
    s32 match_x = tile_x;
    s32 match_y = tile_y;
    void *head = node;
    R10_80174670_S_80174800_4 *actor = head;
    void *owner;

    owner = ((R10_80174670_S_80174800_0_pre *)head)[-1].unk_00;
    node = (u8 *)((R10_80174670_S_80174800_0 *)head)->unk_5C + 0x20;
    while (node != head) {
        R10_80174670_S_80174800_2 *tile = ((R10_80174670_S_80174800_1_pre *)node)[-1].unk_04;
        R10_80174670_S_80174800_3 *height_data = ((R10_80174670_S_80174800_1_pre *)node)[-1].unk_00;
        s16 height;

        if ((tile->unk_24 == (match_x & 0xFFFF)) &&
            (tile->unk_25 == (match_y & 0xFFFF)) &&
            (height = height_data->unk_0A, height <= target_height + 0x38) &&
            (height > target_height - 0x38) &&
            ((u32)(((Rec_func_80174800_arg0 *)node)->unk_13 - 0x33) >= 4U)) {
            actor->unk_84 = 0x7C;
            actor->unk_85 =
                (s8)((s32)(actor->unk_26 * 3) >> 1);
            dungeonPrepareDirectionalAttack(actor, owner,
                          actor->unk_2A, 1, 0);
        }
        node = (u8 *)((Rec_func_80174800_arg0 *)node)->unk_5C + 0x20;
    }
}
