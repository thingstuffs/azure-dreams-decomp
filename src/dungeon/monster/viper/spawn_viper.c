#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/viper/spawn_factory_default.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"

typedef struct S_80170894_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170894_1;   /* work in func_80170894 */

typedef struct S_80170894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170894_2;   /* part_a in func_80170894 */

typedef struct S_80170894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170894_4;   /* actor in func_80170894 */

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern u8 D_80170A68[];
void func_80170E94(void *actor_in, void *actor_data_in, void *sprite_in, void *status_in);
extern u8 viper_frame_set_2[];
extern u8 viper_default_frames[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Viper with default frames at D_80174A7C, applies spawn flags, and attempts valid tile placement. */
void *spawn_mode_configured_monster(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80170894_1 *work;
    S_80170894_4 *actor;
    s32 left;
    s32 right;
    s8 saved_tile_x;
    s16 saved_height;
    s8 saved_tile_y;

    work = 0;
    saved_tile_x = tile_x;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_80170A68;
        work->unk_13 = MONSTER_VIPER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_height;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_tile_y;
        actor = work;
        part_b->frameTable = viper_frame_set_2;
        part_b->tile_x = saved_tile_x;

        if (kind == 1) {
            left = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | ACTOR_CLASS_ENABLED;
            right = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = viper_default_frames;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_80170E94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
