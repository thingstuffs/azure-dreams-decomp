#include "shared/entity.h"
#include "dungeon/monster/glacier.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "dungeon/monster/glacier/advance_item_motion_collision.h"
#include "records/Rec_func_801744DC_arg1.h"
#include "records/Rec_func_801744DC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "sdk/libc.h"

   /* coords in spawn_directional_effect */

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void select_record_entry_and_value(void *, void *, s32);

extern u8 fading_sprite_entries[];

extern Pair16 glacier_direction_offsets[];

/* Spawn an effect with randomized position and velocity based on the source direction. */
void spawn_directional_effect(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin, void *unused)
{
    ObjectNodeHeader *effect;
    DirectionalEffectBody *motion;
    SpriteFrameState *sprite;
    ObjectPosition *position;
    s32 velocity_bias;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = NODE_BODY(effect);
        motion->remaining_ticks.signed_value = 0x4;
        effect->update_callback = advance_item_motion_collision;
        register_node(effect, project_sprite_chain);

        sprite = effect->sprite;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->angle_z = (rand() & 7) << 9;
        sprite->depth_bias = 0;

        position = effect->position;
        position->x.w.i = origin->unk_02;
        position->y.w.i = origin->unk_06;
        position->z.w.i = origin->unk_0A;
        position->x.w.i = ({ (u16)position->x.w.i - 0x20; }) + (rand() & 0x3F);
        position->y.w.i = ({ (u16)position->y.w.i - 0x20; }) + (rand() & 0x3F);
        position->z.w.i = ({ (u16)position->z.w.i - 0x40; }) + (rand() & 0x3F);

        motion->velocity_z = 0xFFFA0000;
        motion->acceleration_z = 0x20000;
        motion->velocity_x = glacier_direction_offsets[source->unk_1C].x << 18;
        motion->velocity_y = glacier_direction_offsets[source->unk_1C].y << 18;

        velocity_bias = 0xFFF80000;
        motion->velocity_x = (motion->velocity_x + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->velocity_y = (motion->velocity_y + velocity_bias) + ((rand() & 0x3FFF) << 6);
        motion->velocity_z = (motion->velocity_z + velocity_bias) + ((rand() & 0x3FFF) << 6);

        sprite = effect->sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags |= 0x100;
        sprite->clut = 0x7DCE;
        select_record_entry_and_value(sprite, fading_sprite_entries, 0);
    }
}
