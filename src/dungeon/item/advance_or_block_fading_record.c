#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/item.h"
#include "slus.h"

typedef struct S_80099B18_1_pre {
    u16 unk_00;
} S_80099B18_1_pre;   /* the 0x2 bytes before arg0 in advance_or_block_fading_record, addressed as arg0[-1] */

typedef struct S_80099B18_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u16 unk_10;
} S_80099B18_1;   /* arg0 in advance_or_block_fading_record */

typedef struct S_80099B18_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80099B18_2;   /* arg1 in advance_or_block_fading_record */

/* Flag blocked records or advance their state, damping motion and fading color when enabled. */
void advance_or_block_fading_record(void *state, S_80099B18_2 *motion, SpriteFrameState *record)
{
    u16 update_count;
    u8 red;
    u8 blue;
    u8 green;

    if (record->flags & 0xE000) {
        ((S_80099B18_1_pre *)state)[-1].unk_00 =
            (s16)(((S_80099B18_1_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    update_count = ((S_80099B18_1 *)state)->unk_10 + 1;
    ((S_80099B18_1 *)state)->unk_10 = update_count;
    if ((update_count << 0x10) > 0) {
        record->flags =
            (u16)(record->flags & 0xFF7F);
        advance_sprite_animation_and_textures(record);
    }
    if (((S_80099B18_1 *)state)->unk_0E != 0) {
        motion->unk_00 =
            (s32)(motion->unk_00 + motion->unk_0C);
        motion->unk_04 =
            (s32)(motion->unk_04 + motion->unk_10);
        motion->unk_08 =
            (s32)(motion->unk_08 + motion->unk_14);
        motion->unk_0C =
            (s32)(motion->unk_0C - (motion->unk_0C >> 2));
        motion->unk_10 =
            (s32)(motion->unk_10 - (motion->unk_10 >> 2));
        motion->unk_14 =
            (s32)(motion->unk_14 - (motion->unk_14 >> 2));
        red = record->color.c.r;
        green = record->color.c.g;
        record->color.c.r =
            (u8)(red - (red >> 1));
        blue = record->color.c.b;
        record->color.c.g =
            (u8)(green - (green >> 1));
        record->color.c.b =
            (u8)(blue - (blue >> 1));
    }
}
