#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "dungeon/monster/kewne.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/monster/kewne_frames.h"

extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 try_move_actor_to_valid_position(void *, void *, void *, void *);

/* Create an entity at the given grid position and initialize its behavior and spawn flags. */
/* Creates Kewne with default frames at D_80175E40, applies spawn flags, and attempts valid tile placement. */
void *create_grid_position_entity(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 height)
{
    ObjectNodeHeader *entity;
    ObjectPosition *position;
    SpriteFrameState *placement;
    ActorRecord *actor;
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
        entity_data = NODE_BODY(entity);
        entity->update_callback = update_actor_callbacks_and_ground;
        ((ActorRecord *)entity_data)->species = MONSTER_KEWNE;
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
            ((ActorRecord *)entity_data)->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((ActorRecord *)entity_data)->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (spawn_mode >= 2) {
            ((ActorRecord *)entity_data)->flags14 |= ACTOR_CLASS_ENABLED;
            ((ActorRecord *)entity_data)->flags1C |= ACTOR_PLAYER_SIDE;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if (!(((u32)((ActorRecord *)entity_data)->flags14) & ACTOR_RESIST_SLEEP)) {
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
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = update_actor_animation_and_behavior;
        ((ActorRecord *)entity_data)->flags1C |= 0x40000;
        actor->unk_90.parts.high.s = -0x20;
        try_move_actor_to_valid_position(actor, position, placement, entity_data);
    }
    return entity_data;
}
