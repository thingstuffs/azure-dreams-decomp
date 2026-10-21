#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_801744DC_arg1.h"
#include "records/Rec_func_801744DC_arg0.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_801746EC_0 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801746EC_0;   /* work in spawn_directional_effect */

typedef struct S_801746EC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801746EC_1;   /* node in spawn_directional_effect */

   /* coords in spawn_directional_effect */

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *, void *, s32);
extern s32 rand(void);

extern u8 D_800DECF8[];
extern s32 D_80174300;
extern Pair16 D_8017610C[];

/* Spawn an effect with randomized position and velocity based on the source direction. */
void spawn_directional_effect(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin)
{
    void *effect;
    S_801746EC_0 *motion;
    SpriteFrameState *sprite;
    MovingPosition *position;
    s32 velocity_bias;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_1E = 0x4;
        ((S_801746EC_1 *)effect)->unk_10 = &D_80174300;
        register_node(effect, project_sprite_chain);

        sprite = ((S_801746EC_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->angle_z = (rand() & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_801746EC_1 *)effect)->unk_08;
        position->unk_02 = origin->unk_02;
        position->unk_06 = origin->unk_06;
        position->unk_0A = origin->unk_0A;
        position->unk_02 = ({ position->unk_02 - 0x20; }) + (rand() & 0x3F);
        position->unk_06 = ({ position->unk_06 - 0x20; }) + (rand() & 0x3F);
        position->unk_0A = ({ position->unk_0A - 0x40; }) + (rand() & 0x3F);

        motion->unk_58 = 0xFFFA0000;
        motion->unk_64 = 0x20000;
        motion->unk_50 = D_8017610C[source->unk_1C].x << 18;
        motion->unk_54 = D_8017610C[source->unk_1C].y << 18;

        velocity_bias = 0xFFF80000;
        motion->unk_50 = (motion->unk_50 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_54 = (motion->unk_54 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_58 = (motion->unk_58 + velocity_bias) + ((rand() & 0x3FFF) << 6);

        sprite = ((S_801746EC_1 *)effect)->unk_0C;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags |= 0x100;
        sprite->clut = 0x7DCE;
        select_record_entry_and_value(sprite, D_800DECF8, 0);
    }
}
