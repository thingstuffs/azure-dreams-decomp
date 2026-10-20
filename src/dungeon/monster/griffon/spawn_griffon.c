#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef struct S_8016A87C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A87C_0;   /* obj in func_8016A87C */

typedef struct S_8016A87C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A87C_1;   /* work in func_8016A87C */

typedef struct S_8016A87C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A87C_2;   /* part_a in func_8016A87C */

typedef struct S_8016A87C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A87C_3;   /* part_b in func_8016A87C */

typedef struct S_8016A87C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A87C_4;   /* actor in func_8016A87C */


extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8016AA50[];
extern u8 D_8016AE7C;
extern u8 D_8016EC3C[];
extern u8 D_8016EC8C[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_8016A87C(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *obj;
    S_8016A87C_2 *part_a;
    S_8016A87C_3 *part_b;
    S_8016A87C_1 *work;
    S_8016A87C_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A87C_0 *)obj)->unk_10 = D_8016AA50;
        work->unk_13 = 0x8;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8016A87C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = ((S_8016A87C_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = D_8016EC3C;
        part_b->unk_24 = saved_kind_id;

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
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a1 = obj;
                call_a1 = obj;
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016EC8C;
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE7C;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
