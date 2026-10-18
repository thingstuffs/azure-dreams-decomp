#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;



typedef struct S_80F45000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80F45000_0;   /* obj in allocate_actor_parts */

typedef struct S_80F45000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F45000_1;   /* work in allocate_actor_parts */

typedef struct S_80F45000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F45000_2;   /* part_a in allocate_actor_parts */

typedef struct S_80F45000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F45000_3;   /* part_b in allocate_actor_parts */

typedef struct S_80F45000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80F45000_4;   /* actor in allocate_actor_parts */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_8015EA68[];
extern M2C_UNK D_8015EE94;
extern u8 D_80162A7C[];
extern u8 D_80162AD4[];




/* Allocate an actor and initialize its parts and behavior from the spawn flags. */
void *allocate_actor_parts(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    void *work = 0;
    void *obj;
    void *part_a;
    register void *part_b;
    S_80F45000_4 *actor;
    register s32 kind;
    s32 random_bits;
    s8 saved_x;
    s16 saved_part_value;
    s8 saved_y;
    void *obj_arg;
    void *part_arg;

    saved_x = tile_x;
    saved_part_value = part_value;
    saved_y = tile_y;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80F45000_0 *)obj)->unk_10 = D_8015EA68;
        ((S_80F45000_1 *)work)->unk_13 = 0x24;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80F45000_0 *)obj)->unk_08;
        ((S_80F45000_2 *)part_a)->unk_0A = saved_part_value;
        part_b = ((S_80F45000_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        ((S_80F45000_3 *)part_b)->unk_25 = saved_y;
        actor = work;
        ((S_80F45000_3 *)part_b)->unk_2C = D_80162A7C;
        ((S_80F45000_3 *)part_b)->unk_24 = saved_x;

        if (kind == 1) {
            ((S_80F45000_1 *)work)->unk_14 |= 0x6000;
            ((S_80F45000_1 *)work)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((S_80F45000_1 *)work)->unk_14 |= 0x2000;
            ((S_80F45000_1 *)work)->unk_1C |= 0x2000;
        } else {
            obj_arg = obj;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_80F45000_1 *)work)->unk_14 & 0x200)) {
                    part_arg = part_a;
                    random_bits = generate_random_value();
                    obj_arg = obj;
                    if (random_bits & 1) {
                        ((S_80F45000_1 *)work)->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        ((S_80F45000_3 *)part_b)->unk_2C = D_80162AD4;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
