#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"

typedef s32 M2C_UNK;

typedef struct S_80B85054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B85054_1;   /* work in func_80B85054 */

typedef struct S_80B85054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B85054_2;   /* part_a in func_80B85054 */

typedef struct S_80B85054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B85054_4;   /* actor in func_80B85054 */

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void set_or_clear_actor_status_slot();
extern u8 D_80158A30[];
extern M2C_UNK D_80158E5C;
extern u8 D_8015BD0C[];
extern u8 D_8015BD4C[];

/* Allocates a dungeon object and initializes its flags, parts, and actor state. */
/* Creates Battnel with default frames at D_8015BD0C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_battnel_actor(s16 spawn_flags, s16 part_byte_24, s16 part_byte_25, s16 part_value)
{
    s32 kind;
    S_80B85054_1 *work = 0;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80B85054_4 *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_part_value;
    s8 saved_byte_25;
    void *part_arg;

    saved_byte_24 = part_byte_24;
    saved_part_value = part_value;
    saved_byte_25 = part_byte_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_80158A30;
        work->unk_13 = MONSTER_BATTNEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_byte_25;
        actor = work;
        part_b->frameTable = D_8015BD0C;
        part_b->tile_x = saved_byte_24;
        do {

            if (kind == 1) {
                flags_or_roll = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                secondary_flags = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                work->unk_14 = flags_or_roll;
                work->unk_1C = secondary_flags;
            } else if (kind >= 2) {
                flags_or_roll = work->unk_14 | ACTOR_CLASS_ENABLED;
                secondary_flags = work->unk_1C | ACTOR_PLAYER_SIDE;
                work->unk_14 = flags_or_roll;
                work->unk_1C = secondary_flags;
            } else {
                part_arg = obj;
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                        part_arg = part_a;
                        flags_or_roll = generate_random_value();
                        part_arg = obj;
                        if (!(flags_or_roll & 1)) {
                            break;
                        }
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value(obj) & 0x3F) | 0x20);
                        part_b->frameTable = D_8015BD4C;
                    }
                }
            }
            part_arg = obj;

        } while (0);
        initialize_actor_sprite_and_animation(part_arg, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80158E5C;
        actor->unk_A4 = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
