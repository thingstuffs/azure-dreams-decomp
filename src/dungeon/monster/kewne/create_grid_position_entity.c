#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"

extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void update_actor_callbacks_and_ground(void *actor, void *motion, SpriteFrameState *sprite);
void update_actor_animation_and_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

extern u8 kewne_frame_set_1[];

typedef struct S_801708B4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_801708B4_1;   /* inner in create_grid_position_entity */


typedef struct S_801708B4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_801708B4_4;   /* result in create_grid_position_entity */

/* Create an entity at the given grid position and initialize its behavior and spawn flags. */
/* Creates Kewne with default frames at D_80175E40, applies spawn flags, and attempts valid tile placement. */
void *create_grid_position_entity(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 height)
{
    ObjectNodeHeader *entity;
    ObjectPosition *position;
    SpriteFrameState *placement;
    S_801708B4_4 *actor;
    s32 spawn_mode;
    s16 saved_flags;
    u8 *entity_data;
    s8 saved_x;
    register s16 saved_height;
    s8 saved_y;

    saved_flags = spawn_flags;
    entity_data = 0;
    saved_x = grid_x;
    saved_height = height;
    saved_y = grid_y;
    entity = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (entity != 0) {
        entity_data = (u8 *)entity + 0x20;
        entity->update_callback = update_actor_callbacks_and_ground;
        ((S_801708B4_1 *)entity_data)->unk_13 = MONSTER_KEWNE;
        register_node(entity, project_sprite_chain);

        position = entity->position;
        position->z.w.i = saved_height;
        placement = entity->sprite;
        spawn_mode = spawn_flags & 3;
        placement->tile_y = saved_y;
        actor = entity_data;
        placement->frameTable = kewne_direction_frames;
        placement->tile_x = saved_x;

        if (spawn_mode == 1) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((S_801708B4_1 *)entity_data)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (spawn_mode >= 2) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= ACTOR_CLASS_ENABLED;
            ((S_801708B4_1 *)entity_data)->unk_1C |= ACTOR_PLAYER_SIDE;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if (!(((S_801708B4_1 *)entity_data)->unk_14 & ACTOR_RESIST_SLEEP)) {
                void *call_entity = entity;
                void *call_position = position;

                if (generate_random_value() & 1) {
                    s32 random_value;
                    void *second_entity = entity;

                    random_value = generate_random_value();

                    set_or_clear_actor_status_slot(entity_data, STATUS_SLEEP, (random_value & 0x3F) | 0x20);
                    placement->frameTable = kewne_frame_set_1;
                }
            }
        }

        initialize_actor_sprite_and_animation(entity, position, placement, saved_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = update_actor_animation_and_behavior;
        ((S_801708B4_1 *)entity_data)->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        try_move_actor_to_valid_position(actor, position, placement, entity_data);
    }
    return entity_data;
}
