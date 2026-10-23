#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_8015E87C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E87C_1;   /* work in create_randomized_flagged_object */

typedef struct S_8015E87C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E87C_2;   /* part_a in create_randomized_flagged_object */

typedef struct S_8015E87C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015E87C_4;   /* actor in create_randomized_flagged_object */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8015EA50[];
extern M2C_UNK D_8015EE7C;
extern u8 D_80162C3C[];
extern u8 D_80162C8C[];

/* Creates a Griffon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_randomized_flagged_object(s16 flags, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_8015E87C_2 *part_a;
    SpriteFrameState *part_b;
    S_8015E87C_1 *work;
    S_8015E87C_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    void *call_a1;

    work = 0;
    saved_arg1 = value_24;
    saved_arg3 = value_0A;
    saved_arg2 = value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8015EA50;
        work->unk_13 = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_arg3;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_arg2;
        actor = work;
        part_b->frameTable = D_80162C3C;
        part_b->tile_x = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind > 1) {
            left = work->unk_14 | ACTOR_CLASS_ENABLED;
            right = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                call_a1 = part_a;
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80162C8C;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE7C;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
