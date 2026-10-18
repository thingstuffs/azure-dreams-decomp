/* Relink of matched dungeon/func_80B73054; every changed retail word is a paired relocation. */
#define D_8016AA30 D_80164A30
#define D_8016AE5C D_80164E5C
#define D_8016DD0C D_80167D0C
#define D_8016DD4C D_80167D4C
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_80B73054_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80B73054_0;   /* obj in func_80164854 */

typedef struct S_80B73054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B73054_1;   /* work in func_80164854 */

typedef struct S_80B73054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B73054_2;   /* part_a in func_80164854 */

typedef struct S_80B73054_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80B73054_3;   /* part_b in func_80164854 */

typedef struct S_80B73054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B73054_4;   /* actor in func_80164854 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80164A30[];
extern M2C_UNK D_80164E5C;
extern u8 D_80167D0C[];
extern u8 D_80167D4C[];

/* Creates a dungeon actor and initializes its parts and state from the spawn flags. */
void *func_80164854(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    s32 kind;
    void *obj;
    S_80B73054_2 *part_a;
    S_80B73054_3 *part_b;
    S_80B73054_1 *work;
    S_80B73054_4 *actor;
    s32 state_bits;
    s32 next_state_bits;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    void *saved_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80B73054_0 *)obj)->unk_10 = D_80164A30;
        work->unk_13 = 0xD;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80B73054_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value;
        part_b = ((S_80B73054_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_80167D0C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            state_bits = work->unk_14 | 0x6000;
            next_state_bits = work->unk_1C | 0x6000;
            work->unk_14 = state_bits;
            work->unk_1C = next_state_bits;
        } else if (kind >= 2) {
            state_bits = work->unk_14 | 0x2000;
            next_state_bits = work->unk_1C | 0x2000;
            work->unk_14 = state_bits;
            work->unk_1C = next_state_bits;
        } else {
            saved_part = obj;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & 0x200)) {
                    saved_part = part_a;
                    state_bits = generate_random_value();
                    saved_part = obj;
                    if (!(state_bits & 1)) {
                        goto init_parts;
                    }
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value(obj) & 0x3F) | 0x20);
                    part_b->unk_2C = D_80167D4C;
                }
            }
        }
        saved_part = obj;
init_parts:
        initialize_actor_sprite_and_animation(saved_part, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80164E5C;
        actor->unk_A4 = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
