#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_801744DC_arg1.h"
#include "records/Rec_func_801744DC_arg0.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_801744DC_0 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801744DC_0;   /* work in spawn_directional_particle */

   /* coords in spawn_directional_particle */

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *, void *, s32);
extern s32 rand(void);

extern u8 shared_sprite_entries[];
extern s32 glacier_object_callback;
extern Pair16 glacier_direction_offsets[];

/* Spawn a particle with randomized position, rotation, and direction-based velocity. */
void spawn_directional_particle(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin)
{
    ObjectNodeHeader *effect;
    S_801744DC_0 *motion;
    SpriteFrameState *sprite;
    MovingPosition *position;
    s32 velocity_bias;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_1E = 0xF;
        effect->update_callback = &glacier_object_callback;
        register_node(effect, project_sprite_chain);

        sprite = effect->sprite;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->angle_z = (rand() & 7) << 9;
        sprite->depth_bias = 0;

        position = effect->position;
        position->x = origin->unk_02;
        position->y = origin->unk_06;
        position->z = origin->unk_0A;
        position->x = ({ position->x - 0x20; }) + (rand() & 0x3F);
        position->y = ({ position->y - 0x20; }) + (rand() & 0x3F);
        position->z = ({ position->z - 0x40; }) + (rand() & 0x3F);

        motion->unk_58 = 0xFFFA0000;
        motion->unk_64 = 0x20000;
        motion->unk_50 = glacier_direction_offsets[source->unk_1C].x << 18;
        motion->unk_54 = glacier_direction_offsets[source->unk_1C].y << 18;

        velocity_bias = 0xFFF80000;
        motion->unk_50 = (motion->unk_50 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_54 = (motion->unk_54 + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->unk_58 = (motion->unk_58 + velocity_bias) + ((rand() & 0x3FFF) << 6);

        sprite = effect->sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags |= 0x100;
        sprite->clut = 0x7DCE;
        select_record_entry_and_value(sprite, shared_sprite_entries, 0);
    }
}
