#include "dungeon/monster/unicorn.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/monster_ids.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

/* The update callback is the shared dragon code at this bank's own address;
 * its canonical name sits at 0x80170A28 and the home bank does not rebind it. */
extern u8 D_80170A50[];
extern ObjectNodeHeader *allocate_list_node(s32, ObjectNodeHeader **);
extern void register_node(ObjectNodeHeader *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(ActorRecord *, s32, s32);
extern void initialize_actor_sprite_and_animation(ObjectNodeHeader *, ObjectPosition *, SpriteFrameState *, s16);
extern void try_move_actor_to_valid_position(void *,void *,void *,void *);

/* Allocate Unicorn, set its spawn state and frames, and try a valid tile. */
void *spawn_unicorn(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
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
        obj->update_callback = D_80170A50;
        work->species = MONSTER_UNICORN;
        register_node(obj, project_sprite_chain);
        position = obj->position;
        position->z.w.i = saved_height;
        sprite = obj->sprite;
        kind = spawn_flags & 3;
        sprite->tile_y = saved_tile_y;
        actor = work;
        sprite->frameTable = unicorn_frame_set;
        sprite->tile_x = saved_tile_x;
        if (kind == 1) {
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind >= 2) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                left = generate_random_value();
                if (left & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    sprite->frameTable = unicorn_sleep_direction_frames;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, position, sprite, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &unicorn_action_continuation_address;
        try_move_actor_to_valid_position(actor, position, sprite, work);
    }
    return work;
}
