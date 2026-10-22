#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_80B85054_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80B85054_0;   /* obj in func_80B85054 */

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

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80158A30[];
extern M2C_UNK D_80158E5C;
extern u8 D_8015BD0C[];
extern u8 D_8015BD4C[];

/* Allocates a dungeon object and initializes its flags, parts, and actor state. */
void *create_battnel_actor(s16 spawn_flags, s16 part_byte_24, s16 part_byte_25, s16 part_value)
{
    s32 kind;
    S_80B85054_1 *work = 0;
    void *obj;
    S_80B85054_2 *part_a;
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
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80B85054_0 *)obj)->unk_10 = D_80158A30;
        work->unk_13 = 0xD;
        register_node(obj, project_sprite_chain);

        part_a = ((S_80B85054_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_value;
        part_b = ((S_80B85054_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_byte_25;
        actor = work;
        part_b->frameTable = D_8015BD0C;
        part_b->unk_24 = saved_byte_24;
        do {

            if (kind == 1) {
                flags_or_roll = work->unk_14 | 0x6000;
                secondary_flags = work->unk_1C | 0x6000;
                work->unk_14 = flags_or_roll;
                work->unk_1C = secondary_flags;
            } else if (kind >= 2) {
                flags_or_roll = work->unk_14 | 0x2000;
                secondary_flags = work->unk_1C | 0x2000;
                work->unk_14 = flags_or_roll;
                work->unk_1C = secondary_flags;
            } else {
                part_arg = obj;
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->unk_14 & 0x200)) {
                        part_arg = part_a;
                        flags_or_roll = generate_random_value();
                        part_arg = obj;
                        if (!(flags_or_roll & 1)) {
                            break;
                        }
                        work->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
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
