#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

typedef long long s64;

typedef struct S_80D35000_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D35000_0;   /* arg1 in move_expand_and_fade_effect_sprite */

typedef struct S_80D35000_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80D35000_1;   /* arg2 in move_expand_and_fade_effect_sprite */

typedef struct S_80D35000_2 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    void * unk_A8;
} S_80D35000_2;   /* arg0 in move_expand_and_fade_effect_sprite */

   /* other in move_expand_and_fade_effect_sprite */


extern void advance_sprite_animation_and_textures(void *);
extern s32 func_80065420(void *, void *, void *, void *);

extern s8 view_direction_depth_biases[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;



/* Move, expand, and fade the effect sprite, marking it for removal when its timer expires. */
/* Moves, damps, expands, and fades the effect sprite, adjusting its draw depth against the stored anchor
 * and facing. */
void move_expand_and_fade_effect_sprite(void *effect, void *motion, void *sprite)
{
    StackWork projection;
    s16 ticks_left;
    s16 fade_ticks;
    s32 effect_depth;
    s32 scale_or_shade;
    MovingPosition *anchor;

    ((S_80D35000_0 *)motion)->unk_00.at00.v += ((S_80D35000_0 *)motion)->unk_0C;
    ((S_80D35000_0 *)motion)->unk_04.at00.v += ((S_80D35000_0 *)motion)->unk_10;
    ((S_80D35000_0 *)motion)->unk_08.at00.v += ((S_80D35000_0 *)motion)->unk_14;
    ((S_80D35000_0 *)motion)->unk_0C = ((S_80D35000_0 *)motion)->unk_0C * 9 / 10;
    ((S_80D35000_0 *)motion)->unk_10 = ((S_80D35000_0 *)motion)->unk_10 * 9 / 10;
    ((S_80D35000_0 *)motion)->unk_14 = ((S_80D35000_0 *)motion)->unk_14 * 8 / 10;

    if (((S_80D35000_1 *)sprite)->unk_1C == 0) {
        ((S_80D35000_1 *)sprite)->unk_1E = 0x400;
        ((S_80D35000_1 *)sprite)->unk_1C = 0x400;
    }

    scale_or_shade = ((S_80D35000_1 *)sprite)->unk_1E + 0x32;
    ((S_80D35000_1 *)sprite)->unk_1E = scale_or_shade;
    ((S_80D35000_1 *)sprite)->unk_1C = scale_or_shade;

    projection.xyz[0] = ((S_80D35000_0 *)motion)->unk_00.at02.v;
    projection.xyz[1] = ((S_80D35000_0 *)motion)->unk_04.at02.v;
    projection.xyz[2] = ((S_80D35000_0 *)motion)->unk_08.at02.v;
    effect_depth = func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24);

    anchor = ((S_80D35000_2 *)effect)->unk_A8;
    projection.xyz[0] = anchor->unk_02;
    projection.xyz[1] = anchor->unk_06;
    projection.xyz[2] = anchor->unk_0A;
    ((S_80D35000_1 *)sprite)->unk_06 = effect_depth -
        func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24) -
        view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80D35000_2 *)effect)->unk_94 + 0x100) >> 9) & 7] * 2;

    fade_ticks = ((S_80D35000_2 *)effect)->unk_96.s;
    if (fade_ticks < 10) {
        ((S_80D35000_1 *)sprite)->unk_10 = 0x20;
        ((S_80D35000_1 *)sprite)->unk_12 = 0xFF80;
        ((S_80D35000_1 *)sprite)->unk_14 |= 0xC;
        scale_or_shade = (fade_ticks << 7) / 10;
        ((S_80D35000_1 *)sprite)->unk_0E = scale_or_shade;
        ((S_80D35000_1 *)sprite)->unk_0D = scale_or_shade;
        ((S_80D35000_1 *)sprite)->unk_0C = scale_or_shade;
    }

    advance_sprite_animation_and_textures(sprite);
    ticks_left = ((S_80D35000_2 *)effect)->unk_96.u - 1;
    ((S_80D35000_2 *)effect)->unk_96.u = ticks_left;
    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
