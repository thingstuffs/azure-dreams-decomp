#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170894_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170894_0;   /* obj in func_80170894 */

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

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80170A68[];
void func_80170E94(void *actor_in, void *actor_data_in, void *sprite_in, void *status_in);
extern u8 D_80174A7C[];
extern u8 D_80174AD4[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_80170894(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *obj;
    S_80170894_2 *part_a;
    SpriteFrameState *part_b;
    S_80170894_1 *work;
    S_80170894_4 *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80170894_0 *)obj)->unk_10 = D_80170A68;
        work->unk_13 = 0x24;
        register_node(obj, project_sprite_chain);

        part_a = ((S_80170894_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((S_80170894_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->frameTable = D_80174A7C;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80174AD4;
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
