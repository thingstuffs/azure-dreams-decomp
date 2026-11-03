#include "common.h"
#include "records/Rec_func_80174800_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct S_80174800_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174800_0_pre;   /* the 0x14 bytes before head in create_randomly_rotated_offset_effect, addressed as head[-1] */

typedef struct S_80174800_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80174800_0;   /* head in create_randomly_rotated_offset_effect */

typedef struct S_80174800_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80174800_1_pre;   /* the 0x18 bytes before arg0 in create_randomly_rotated_offset_effect, addressed as arg0[-1] */




typedef struct S_80174800_4 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 pad_27[0x3];
    s16 unk_2A;
    u8 pad_2C[0x58];
    s8 unk_84;
    s8 unk_85;
} S_80174800_4;   /* actor in create_randomly_rotated_offset_effect */


extern s32 prepare_directional_attack();

/*
 * Scans the actor ring at the target tile and height, preparing an attack for each entry outside
 * classes 0x33-0x36.
 */
void create_randomly_rotated_offset_effect(void *node, s32 tile_x, s32 tile_y, s16 target_height)
{
    s32 match_x = tile_x;
    s32 match_y = tile_y;
    void *head = node;
    S_80174800_4 *actor = head;
    void *owner;

    owner = ((S_80174800_0_pre *)head)[-1].unk_00;
    node = (u8 *)((S_80174800_0 *)head)->unk_5C + 0x20;
    while (node != head) {
        SpriteFrameState *tile = ((S_80174800_1_pre *)node)[-1].unk_04;
        ObjectPosition *height_data = ((S_80174800_1_pre *)node)[-1].unk_00;
        s16 height;

        if ((tile->tile_x == (match_x & 0xFFFF)) &&
            (tile->tile_y == (match_y & 0xFFFF)) &&
            (height = height_data->z.w.i, height <= target_height + 0x38) &&
            (height > target_height - 0x38) &&
            ((u32)(((Rec_func_80174800_arg0 *)node)->unk_13 - 0x33) >= 4U)) {
            actor->unk_84 = 0x7C;
            actor->unk_85 =
                (s8)((s32)(actor->unk_26 * 3) >> 1);
            prepare_directional_attack(actor, owner,
                          actor->unk_2A, 1, 0);
        }
        node = (u8 *)((Rec_func_80174800_arg0 *)node)->unk_5C + 0x20;
    }
}
