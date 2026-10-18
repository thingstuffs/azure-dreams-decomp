#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170F9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170F9C_0;   /* object in create_configured_actor_sprite */

typedef struct S_80170F9C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80170F9C_1;   /* work in create_configured_actor_sprite */

typedef struct S_80170F9C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170F9C_2;   /* part_a in create_configured_actor_sprite */

typedef struct S_80170F9C_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170F9C_3;   /* part_b in create_configured_actor_sprite */

typedef struct S_80170F9C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x18];
    s8 unk_B5;
} S_80170F9C_4;   /* work_copy in create_configured_actor_sprite */


extern void *func_8003FD64();
extern void func_8004491C();
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern void create_owner_linked_directional_object();

extern u8 D_800E23E0[];
extern u8 D_800E2428[];
extern u8 D_801711B0[];
extern u8 D_80171A80[];

void *create_configured_actor_sprite(s16 mode, s16 value_24, s16 value_25, s16 value_0A)
{
    s8 held_value_24 = value_24;
    s16 held_value_0A = value_0A;
    s8 held_value_25 = value_25;
    s16 mode_copy;
    s32 kind;
    u16 saved_x;
    u16 saved_y;
    void *object;
    S_80170F9C_2 *part_a;
    S_80170F9C_3 *part_b;
    S_80170F9C_1 *work;
    S_80170F9C_4 *work_copy;

    work = 0;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    mode_copy = mode;
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_80170F9C_0 *)object)->unk_10 = D_801711B0;
        work->unk_13 = 0x18;
        func_8004491C(object, func_80045340);

        part_a = ((S_80170F9C_0 *)object)->unk_08;
        kind = mode & 3;
        part_a->unk_0A = held_value_0A;
        part_b = ((S_80170F9C_0 *)object)->unk_0C;
        work_copy = work;
        part_b->unk_2C = D_800E23E0;
        part_b->unk_24 = held_value_24;
        part_b->unk_25 = held_value_25;

        if (kind == 1) {
            work->unk_14 |= 0x6000;
            work->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            work->unk_14 |= 0x2000;
            work->unk_1C |= 0x2000;
        } else if (((mode & -4) << 16) == 0) {
            if ((work->unk_14 & 0x200) == 0) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_800E2428;
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, mode_copy);
        work_copy->unk_9A = 0xFF;
        work_copy->unk_9C = -1;
        work_copy->unk_8C = D_80171A80;
        work->unk_1C |= 0x40000;
        work_copy->unk_92 = -0x20;
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);

        work_copy->unk_B5 = 0;
        saved_x = part_b->unk_1C;
        saved_y = part_b->unk_1E;
        part_b->unk_1C = 0;
        part_b->unk_1E = 0;
        create_owner_linked_directional_object(work_copy, part_a, part_b);
        part_b->unk_1C = saved_x;
        part_b->unk_1E = saved_y;
    }

    return work;
}

/* MECHANISM: Ordered value_24/value_0A/value_25 homes plus an s5 part_a base reproduce the 0x38 frame
   and retail save/hold set; ASM_USE keeps s6/s7 occupied so the mode copy takes fp.
   Both generate_random_value sites are zero-argument RNG calls, leaving their delay slots as nops. */
