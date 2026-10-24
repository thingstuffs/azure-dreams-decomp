#include "dungeon/monster/unicorn.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/monster_ids.h"

/* The factory also writes the species byte and callback fields for which
 * ActorRecord retains an opaque aggregate. Both views describe the same body. */
typedef union SpawnState {
    ActorRecord actor;
    struct {
        u8 pad_00[0x13];
        u8 species;
        u8 pad_14[0x78];
        void *action;
        u8 pad_90[0xA];
        u8 action_index;
        u8 pad_9B;
        s8 unk_9C;
    } fields;
} SpawnState;

extern ObjectNodeHeader *allocate_list_node(s32, ObjectNodeHeader *);
extern void register_node(ObjectNodeHeader *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(ActorRecord *, s32, s32);
extern void initialize_actor_sprite_and_animation(ObjectNodeHeader *, ObjectPosition *, SpriteFrameState *, s16);
extern void try_move_actor_to_valid_position(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
extern u8 D_80170A50[], D_80174D4C[], D_80174DB4[], D_80170E7C[];

/* Allocate Unicorn, set its spawn state and frames, and try a valid tile. */
void *spawn_unicorn(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    SpawnState *work;
    SpawnState *actor;
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
    obj = allocate_list_node(0x112, &scene_object_list_anchor);
    if (obj != 0) {
        body = obj + 1;
        work = body;
        obj->update_callback = D_80170A50;
        work->fields.species = MONSTER_UNICORN;
        register_node(obj, project_sprite_chain);
        position = obj->position;
        position->z.w.i = saved_height;
        sprite = obj->sprite;
        kind = spawn_flags & 3;
        sprite->tile_y = saved_tile_y;
        actor = work;
        sprite->frameTable = D_80174D4C;
        sprite->tile_x = saved_tile_x;
        if (kind == 1) {
            left = work->actor.flags14 | 0x6000;
            right = work->actor.flags1C | 0x6000;
            work->actor.flags14 = left;
            work->actor.flags1C = right;
        } else if (kind >= 2) {
            left = work->actor.flags14 | 0x2000;
            right = work->actor.flags1C | 0x2000;
            work->actor.flags14 = left;
            work->actor.flags1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->actor.flags14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->actor.flags1C |= 0x200;
                    set_or_clear_actor_status_slot(&work->actor, 1, (generate_random_value() & 0x3F) | 0x20);
                    sprite->frameTable = D_80174DB4;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, position, sprite, spawn_flags);
        actor->fields.action_index = 0xFF;
        actor->fields.unk_9C = -1;
        actor->fields.action = D_80170E7C;
        try_move_actor_to_valid_position(&actor->actor, position, sprite, &work->actor);
    }
    return work;
}
