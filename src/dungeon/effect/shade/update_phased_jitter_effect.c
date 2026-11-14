#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "sdk/libc.h"
#include "dungeon/effect/shade.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

typedef struct S_800D50FC_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xF];
    u16 unk_1E;
    s16 unk_20;
} S_800D50FC_0;   /* body fields read by update_phased_jitter_effect */

typedef struct S_800D50FC_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800D50FC_3;   /* page in update_phased_jitter_effect */



/* Updates effect motion and color, then marks it inactive when its lifetime expires. */
void update_phased_jitter_effect(void *effect, ObjectPosition *motion, SpriteFrameState *color) {
    s32 y_speed;
    u16 life_left;
    u32 phase;

    phase = ((S_800D50FC_0 *)effect)->unk_1E & 7;
    switch (phase) {
    case 1:
    case 2:
    case 5:
    case 6:
        break;
    case 0:
    case 4:
        motion->velocity_x = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        y_speed = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        motion->velocity_y = y_speed;
        break;
    case 3:
    case 7:
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        break;
    }
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    color->color.c.r = (s8) ((s32) (((S_800D50FC_0 *)effect)->unk_0C * (s16) ((S_800D50FC_0 *)effect)->unk_1E) / (s16) ((S_800D50FC_0 *)effect)->unk_20);
    color->color.c.g = (s8) ((s32) (((S_800D50FC_0 *)effect)->unk_0D * (s16) ((S_800D50FC_0 *)effect)->unk_1E) / (s16) ((S_800D50FC_0 *)effect)->unk_20);
    color->color.c.b = (s8) ((s32) (((S_800D50FC_0 *)effect)->unk_0E * (s16) ((S_800D50FC_0 *)effect)->unk_1E) / (s16) ((S_800D50FC_0 *)effect)->unk_20);
    life_left = ((S_800D50FC_0 *)effect)->unk_1E - 1;
    ((S_800D50FC_0 *)effect)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        u32 page;

        page = 0x80080000;
        NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | 0x8000);
        ((S_800D50FC_3 *)page)->unk_14A0 = ((S_800D50FC_3 *)page)->unk_14A0 | 0x8000;
    }
}
