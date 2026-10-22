#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_8015E87C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E87C_0;   /* obj in create_randomized_flagged_object */

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
    void *obj;
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
        ((S_8015E87C_0 *)obj)->unk_10 = D_8015EA50;
        work->unk_13 = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8015E87C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8015E87C_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->frameTable = D_80162C3C;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind > 1) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
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
