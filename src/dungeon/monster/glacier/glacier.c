#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8102F348_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_8102F348_0;   /* arg1 in func_8102F348 */

typedef struct S_8102F348_1_pre {
    u16 unk_00;
} S_8102F348_1_pre;   /* the 0x2 bytes before arg0 in func_8102F348, addressed as arg0[-1] */

typedef struct S_8102F348_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    u16 unk_20;
    u8 pad_22[0x2E];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
} S_8102F348_1;   /* arg0 in func_8102F348 */

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void advance_sprite_animation_and_textures(void *);
/* Updates effect motion and collision, grows its sprite, and flags expired effects. */
void grow_terrain_colliding_sprite(void *effect, S_8102F348_0 *position, SpriteFrameState *sprite) {
    s32 height;

    position->unk_00.at00.v += ((S_8102F348_1 *)effect)->unk_50;
    ((S_8102F348_1 *)effect)->unk_50 += ((S_8102F348_1 *)effect)->unk_5C;
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v,
                       position->unk_08.at02.v) << 16) != 0) {
        position->unk_00.at00.v -= ((S_8102F348_1 *)effect)->unk_50;
        ((S_8102F348_1 *)effect)->unk_50 = 0;
        ((S_8102F348_1 *)effect)->unk_5C = 0;
    }

    position->unk_04.at00.v += ((S_8102F348_1 *)effect)->unk_54;
    ((S_8102F348_1 *)effect)->unk_54 += ((S_8102F348_1 *)effect)->unk_60;
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v,
                       position->unk_08.at02.v) << 16) != 0) {
        position->unk_04.at00.v -= ((S_8102F348_1 *)effect)->unk_54;
        ((S_8102F348_1 *)effect)->unk_54 = 0;
        ((S_8102F348_1 *)effect)->unk_60 = 0;
    }

    position->unk_08.at00.v += ((S_8102F348_1 *)effect)->unk_58;
    ((S_8102F348_1 *)effect)->unk_58 += ((S_8102F348_1 *)effect)->unk_64;
    height = position->unk_08.at02.v;
    if ((sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v,
                       (s16)((u16)position->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_8102F348_1 *)effect)->unk_58 = 0;
        position->unk_08.at02.v = sample_terrain_surface_height(
            position->unk_00.at02.v, position->unk_04.at02.v,
            (s16)((u16)position->unk_08.at02.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
        if (((S_8102F348_1 *)effect)->unk_14 == 0) {
            ((S_8102F348_1 *)effect)->unk_14 = 1;
            ((S_8102F348_1 *)effect)->unk_1E.s = 0;
        }
    }

    ((S_8102F348_1 *)effect)->unk_20++;
    if ((((S_8102F348_1 *)effect)->unk_20 & 3) == 0) {
        advance_sprite_animation_and_textures(sprite);
    }

    sprite->scale_x += 100;
    if (sprite->scale_x > 0x1000) {
        sprite->scale_x = 0x1000;
    }

    sprite->scale_y += 100;
    if (sprite->scale_y > 0x1000) {
        sprite->scale_y = 0x1000;
    }

    ((S_8102F348_1 *)effect)->unk_1E.u = ((S_8102F348_1 *)effect)->unk_1E.u - 1;
    if ((s16)((S_8102F348_1 *)effect)->unk_1E.u <= 0) {
        s32 *status_page = (s32 *)0x80080000;
        ((S_8102F348_1_pre *)effect)[-1].unk_00 |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }

    if (sprite->flags & 0x8000) {
        s32 *status_page = (s32 *)0x80080000;
        ((S_8102F348_1_pre *)effect)[-1].unk_00 |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }
}
