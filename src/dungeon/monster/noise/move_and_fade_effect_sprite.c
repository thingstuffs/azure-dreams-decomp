#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

typedef long long s64;

typedef struct S_80D23000_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D23000_0;   /* arg1 in move_and_fade_effect_sprite */

typedef struct S_80D23000_2 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    void * unk_A8;
} S_80D23000_2;   /* arg0 in move_and_fade_effect_sprite */

   /* other in move_and_fade_effect_sprite */

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

/* Move, expand, and fade an effect sprite, marking it expired when its lifetime ends. */
/* Moves, damps, expands, and fades the effect sprite, adjusting its draw depth against the stored origin
 * and facing. */
void move_and_fade_effect_sprite(void *effect, void *motion, SpriteFrameState *sprite)
{
    StackWork projection;
    s16 next_life;
    s16 life;
    s32 depth;
    s32 scale_or_shade;
    MovingPosition *origin;

    ((S_80D23000_0 *)motion)->unk_00.at00.v += ((S_80D23000_0 *)motion)->unk_0C;
    ((S_80D23000_0 *)motion)->unk_04.at00.v += ((S_80D23000_0 *)motion)->unk_10;
    ((S_80D23000_0 *)motion)->unk_08.at00.v += ((S_80D23000_0 *)motion)->unk_14;
    ((S_80D23000_0 *)motion)->unk_0C = ((S_80D23000_0 *)motion)->unk_0C * 9 / 10;
    ((S_80D23000_0 *)motion)->unk_10 = ((S_80D23000_0 *)motion)->unk_10 * 9 / 10;
    ((S_80D23000_0 *)motion)->unk_14 = ((S_80D23000_0 *)motion)->unk_14 * 8 / 10;

    if (sprite->scale_x == 0) {
        sprite->scale_y = 0x400;
        sprite->scale_x = 0x400;
    }

    scale_or_shade = sprite->scale_y + 0x32;
    sprite->scale_y = scale_or_shade;
    sprite->scale_x = scale_or_shade;

    projection.xyz[0] = ((S_80D23000_0 *)motion)->unk_00.at02.v;
    projection.xyz[1] = ((S_80D23000_0 *)motion)->unk_04.at02.v;
    projection.xyz[2] = ((S_80D23000_0 *)motion)->unk_08.at02.v;
    depth = func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24);

    origin = ((S_80D23000_2 *)effect)->unk_A8;
    projection.xyz[0] = origin->unk_02;
    projection.xyz[1] = origin->unk_06;
    projection.xyz[2] = origin->unk_0A;
    sprite->unk_06 = depth -
        func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24) -
        view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80D23000_2 *)effect)->unk_94 + 0x100) >> 9) & 7] * 2;

    life = ((S_80D23000_2 *)effect)->unk_96.s;
    if (life < 10) {
        sprite->tpage_abr = 0x20;
        sprite->clut = 0xFF80;
        sprite->flags |= 0xC;
        scale_or_shade = (life << 7) / 10;
        sprite->color.c.b = scale_or_shade;
        sprite->color.c.g = scale_or_shade;
        sprite->color.c.r = scale_or_shade;
    }

    advance_sprite_animation_and_textures(sprite);
    next_life = ((S_80D23000_2 *)effect)->unk_96.u - 1;
    ((S_80D23000_2 *)effect)->unk_96.u = next_life;
    if ((next_life << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
