#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity.h"
#include "dungeon/monster/nyuel/spawn_factory_default.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170894_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80170894_0;   /* work in func_80170894 */

typedef struct S_80170894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170894_4;   /* actor in func_80170894 */

extern void *allocate_list_node(s32, const void *);
extern void register_node(void *, const void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern void update_monster_facing_and_contact(void);
extern void update_entity_actions_facing_and_animation(void);
extern void func_80174ED8(void);
extern void func_80174F00(void);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Nyuel with spawn-mode flags and frames at func_80174ED8, then initializes its callbacks and tile
 * placement. */
void *spawn_mode_configured_monster(s32 spawn_flags, s8 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    void *work;
    s16 saved_height;
    s32 held_flags;
    ObjectNodeHeader *obj;
    s8 saved_tile_y;
    s8 saved_tile_x;
    ObjectPosition *part_a;
    s16 flags_copy;
    s32 call_id;
    ObjectNodeHeader *call_target;

    held_flags = spawn_flags;
    work = 0;
    call_id = 0x112;
    saved_tile_x = tile_x;
    call_target = &scene_object_list_anchor;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(call_id, call_target);
    flags_copy = held_flags;
    if (obj != 0) {
        register SpriteFrameState *part_b;
        void *actor;

        work = (u8 *)obj;
        work += 0x20;
        ((S_80170894_0 *)work)->unk_13 = MONSTER_NYUEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_height;
        part_b = obj->sprite;
        kind = held_flags & 3;
        part_b->unk_25 = saved_tile_y;
        actor = work;
        part_b->unk_24 = saved_tile_x;

        if (kind == 1) {
            s32 left_one;
            s32 right_one;

            ((S_80170894_0 *)work)->unk_8C = update_entity_actions_facing_and_animation;
            left_one = ((ObjectNodeHeader *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right_one = *(s32 *)&((ObjectNodeHeader *)work)->pad_1C | 0x6000;
            ((ObjectNodeHeader *)work)->unk_14 = left_one;
            *(s32 *)&((ObjectNodeHeader *)work)->pad_1C = right_one;
            part_b->frameTable = func_80174ED8;
        } else if (kind >= 2) {
            s32 left_many;
            s32 right_many;

            ((S_80170894_0 *)work)->unk_8C = update_entity_actions_facing_and_animation;
            left_many = ((ObjectNodeHeader *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            right_many = *(s32 *)&((ObjectNodeHeader *)work)->pad_1C | 0x2000;
            ((ObjectNodeHeader *)work)->unk_14 = left_many;
            *(s32 *)&((ObjectNodeHeader *)work)->pad_1C = right_many;
            part_b->frameTable = func_80174ED8;
        } else {
            s32 test;
            u8 *callback_page;

            test = held_flags & ~3;
            test <<= 16;
            if (test != 0) {
                callback_page = (u8 *)0x80170000;
            } else {
                if (((ObjectNodeHeader *)work)->unk_14 & ACTOR_RESIST_SLEEP) {
                    callback_page = (u8 *)0x80170000;
                } else if (!(generate_random_value() & 1)) {
                    callback_page = (u8 *)0x80170000;
                } else {
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = func_80174F00;
                    callback_page = (u8 *)0x80170000;
                }
                ((S_80170894_4 *)actor)->unk_8C = callback_page + 0xE9C;
                part_b->frameTable = func_80174ED8;
                goto callback_done;
            }
            ((S_80170894_0 *)work)->unk_8C = callback_page + 0xE9C;
            part_b->frameTable = func_80174ED8;
        }
callback_done:
        obj->unk_10 = update_monster_facing_and_contact;
        initialize_actor_sprite_and_animation(obj, part_a, part_b, flags_copy);
        ((S_80170894_4 *)actor)->unk_9A = 0xFF;
        ((S_80170894_4 *)actor)->unk_9C = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
