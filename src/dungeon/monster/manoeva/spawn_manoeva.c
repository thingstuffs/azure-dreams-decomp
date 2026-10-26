#include "dungeon/monster/manoeva.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/monster_ids.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"

/* The factory also stores the strength variant in the low byte of +0xAC, which
 * ActorRecord types as the saved callback pointer (unk_AC); the view reaches it. */
typedef union SpawnState {
    ActorRecord actor;
    struct {
        u8 pad_00[0xAC];
        u8 variant;
    } fields;
} SpawnState;

extern ObjectNodeHeader *allocate_list_node(s32, ObjectNodeHeader **);
extern void register_node(ObjectNodeHeader *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(ActorRecord *, s32, s32);
extern void initialize_actor_sprite_and_animation(ObjectNodeHeader *, ObjectPosition *, SpriteFrameState *, s16);
extern void try_move_actor_to_valid_position(void *,void *,void *,void *);
extern void create_terrain_scaled_actor_effect(ObjectNodeHeader *, s16 *, u8 *, u16 *);
extern u8 entity_spawn_variant_code;
extern u8 manoeva_frame_set_1[], manoeva_sleep_frames[], manoeva_action_resume_address[];

/* Allocate Manoeva, set its spawn state, frames and strength variant, and try a valid tile. */
void *spawn_manoeva(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    SpawnState *work;
    SpawnState *actor;
    s8 saved_tile_x;
    s16 saved_height;
    s8 saved_tile_y;
    void *body;

    work = 0;
    saved_tile_x = tile_x;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        body = obj + 1;
        work = body;
        obj->update_callback = update_effect_visuals_and_lifetime;
        work->actor.species = MONSTER_MANOEVA;
        register_node(obj, project_sprite_chain);
        position = obj->position;
        position->z.w.i = saved_height;
        sprite = obj->sprite;
        sprite->tile_x = saved_tile_x;
        sprite->tile_y = saved_tile_y;
        kind = spawn_flags & 3;
        actor = work;
        sprite->frameTable = manoeva_frame_set_1;
        if (kind == 1) {
            work->actor.flags14 |= ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER;
            work->actor.flags1C |= ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER;
        } else if (kind >= 2) {
            work->actor.flags14 |= ACTOR_CLASS_ENABLED;
            work->actor.flags1C |= ACTOR_PLAYER_SIDE;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->actor.flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(&work->actor, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    sprite->frameTable = manoeva_sleep_frames;
                }
            }
            if (entity_spawn_variant_code < 10) {
                actor->fields.variant = 2;
            } else if (entity_spawn_variant_code < 20) {
                actor->fields.variant = 1;
            } else {
                actor->fields.variant = 0;
            }
        }
        initialize_actor_sprite_and_animation(obj, position, sprite, spawn_flags);
        actor->actor.action_id = 0xFF;
        actor->actor.unk_9C = -1;
        actor->actor.unk_8C.address = manoeva_action_resume_address;
        create_terrain_scaled_actor_effect(obj, &work->actor.facing, &actor->actor.action_id,
                                           &actor->actor.action_state_flags);
        try_move_actor_to_valid_position(&actor->actor, position, sprite, &work->actor);
    }
    return work;
}
