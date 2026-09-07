#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BD688_9 {
    void * unk_00;
    void * unk_04;
} S_800BD688_9;   /* arg0 in func_800BD688 */

typedef struct S_800BD688_10 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800BD688_10;   /* ((S_800BD688_9 *)arg0)->unk_00 in func_800BD688 */

typedef struct S_800BD688_11 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800BD688_11;   /* ((S_800BD688_9 *)arg0)->unk_04 in func_800BD688 */


typedef struct S_800BD688_0_pre {
    u16 unk_00;
} S_800BD688_0_pre;   /* the 0x2 bytes before arg0 in func_800BD688, addressed as arg0[-1] */

typedef struct S_800BD688_0 {
    void * unk_00;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0x14];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u16 unk_22;
} S_800BD688_0;   /* arg0 in func_800BD688 */

typedef struct S_800BD688_1 {
    s32 unk_00;
} S_800BD688_1;   /* left_ptr in func_800BD688 */

typedef struct S_800BD688_2 {
    s32 unk_00;
} S_800BD688_2;   /* right_ptr in func_800BD688 */

typedef struct S_800BD688_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BD688_3;   /* var_a0 in func_800BD688 */

typedef struct S_800BD688_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BD688_4;   /* temp_v1_2 in func_800BD688 */

typedef struct S_800BD688_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800BD688_5;   /* temp_v1_3 in func_800BD688 */

typedef struct S_800BD688_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800BD688_6;   /* temp_a0 in func_800BD688 */

typedef struct S_800BD688_7 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800BD688_7;   /* temp_a1 in func_800BD688 */

typedef struct S_800BD688_8 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800BD688_8;   /* temp_a0_2 in func_800BD688 */


s32 rand(void);                      /* extern */

/* Randomize paired object motion until both pass the stop position, then set completion flags. */
void func_800BD688(void *pair_in) {
    void *pair = pair_in;
    s32 state;
    s32 random_value;
    s32 stop_x;
    s32 speed_limit;
    s32 speed_bias;
    s32 member_index;
    register s32 x_gap ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 x_speed;
    u16 tick;
    register s32 *flag_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    void **member_slot;
    S_800BD688_6 *second_depth;
    S_800BD688_8 *second_motion;
    S_800BD688_7 *first_motion;
    S_800BD688_4 *x_motion;
    S_800BD688_5 *y_motion;
    S_800BD688_3 *member_motion;

    state = ((S_800BD688_0 *)pair)->unk_20.s;
    tick = (((S_800BD688_0 *)pair)->unk_22 + 1) & 7;
    ((S_800BD688_0 *)pair)->unk_22 = tick;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    member_motion = (void *)0xFEC00000;
    if (tick == 0) {
        {
            S_800BD688_1 *first_position;
            S_800BD688_2 *second_position;

            first_position = ((S_800BD688_0 *)pair)->unk_00;
            second_position = ((S_800BD688_0 *)pair)->unk_04;
            x_gap = first_position->unk_00;
            x_gap -= second_position->unk_00;
        }
        if (x_gap < 0) {
            x_gap = 0 - x_gap;
        }
        ASM_KEEP(x_gap);   /* MATCH pin: retail basic-block layout depends on it */
        {
            register u32 gap_offset ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

            gap_offset = x_gap + 0xFFE00000;
            if (gap_offset > 0x200000U) {
                member_index = 1;
                speed_limit = 0x7FFFF;
                speed_bias = 0xFFF80000;
                member_slot = pair + 4;
                do {
                    random_value = rand();
                    member_motion = *member_slot;
                    x_speed = (random_value & 0x1FF) << 8;
                    if (member_motion->unk_0C > speed_limit) {
                        x_speed = 0 - x_speed;
                    }
                    member_motion->unk_0C = x_speed;
                    x_motion = *member_slot;
                    member_slot = (void **)((s8 *)((void **)((s8 *)member_slot - 4)));
                    member_index -= 1;
                    x_motion->unk_0C = (s32) (x_motion->unk_0C + speed_bias);
                } while (member_index >= 0);
            }
        }
        member_index = 1;
        member_slot = pair + 4;
        do {
            random_value = rand();
            member_index -= 1;
            y_motion = *member_slot;
            member_slot = (void **)((s8 *)((void **)((s8 *)member_slot - 4)));
            y_motion->unk_10 = (s32) (((random_value & 0x1FF) - 0x100) << 9);
        } while (member_index >= 0);
        ((S_800BD688_10 *)(((S_800BD688_9 *)pair)->unk_00))->unk_14 = (s32) (((rand() & 0x1FF) - 0x100) << 8);
        ((S_800BD688_11 *)(((S_800BD688_9 *)pair)->unk_04))->unk_14 = (s32) ((rand() & 0x1FF) << 7);
        second_depth = ((S_800BD688_0 *)pair)->unk_04;
        if (((S_800BD688_10 *)(((S_800BD688_9 *)pair)->unk_00))->unk_08 < second_depth->unk_08) {
            second_depth->unk_14 = (s32) (0 - second_depth->unk_14);
        }
    }
    first_motion = ((S_800BD688_0 *)pair)->unk_00;
    stop_x = ((S_800BD688_0 *)pair)->unk_08 + 0xFEC00000;
    if (first_motion->unk_00 < stop_x) {
        second_motion = ((S_800BD688_0 *)pair)->unk_04;
        if (second_motion->unk_00 < stop_x) {
            second_motion->unk_0C = 0;
            first_motion->unk_0C = 0;
            ((S_800BD688_0 *)pair)->unk_20.u += 1;
        }
    }
    goto done;

state_one:
    flag_page = (s32 *)0x80080000;
    ASM_KEEP(flag_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_800BD688_0_pre *)pair)[-1].unk_00 = (u16) (((S_800BD688_0_pre *)pair)[-1].unk_00 | 0x8000);
    flag_page[0x14A0 / 4] |= 0x8000;

done:
    return;
}
