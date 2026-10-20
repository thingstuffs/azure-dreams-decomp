#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800C5A64_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0xA];
    s16 unk_1C;
} S_800C5A64_1;   /* arg0 in damp_effect_motion_and_fade */

extern void func_800478B8();

/* Advance and damp effect motion, fade its primitive, and mark it expired when its lifetime ends. */
void damp_effect_motion_and_fade(void *effect, s32 *motion, SpriteFrameState *primitive)
{
    s16 remaining;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[3] -= motion[3] >> 3;
    motion[4] -= motion[4] >> 3;

    func_800478B8(primitive);

    primitive->color.c.r -= primitive->color.c.r / ((S_800C5A64_1 *)effect)->unk_10.s;
    primitive->color.c.g -= primitive->color.c.g / ((S_800C5A64_1 *)effect)->unk_10.s;
    primitive->color.c.b -= primitive->color.c.b / ((S_800C5A64_1 *)effect)->unk_10.s;

    remaining = ((S_800C5A64_1 *)effect)->unk_10.u - 1;
    ((S_800C5A64_1 *)effect)->unk_10.s = remaining;
    if ((remaining << 16) <= 0) {
        if ((((S_800C5A64_1 *)effect)->unk_0C == 0) &&
            (((S_800C5A64_1 *)effect)->unk_1C == 0)) {
            g_dungeon_status.unk_0A--;
        }
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
