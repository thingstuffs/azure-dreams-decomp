#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_81934C5C_0_pre {
    u16 unk_00;
} S_81934C5C_0_pre;   /* the 0x2 bytes before arg0 in func_81934C5C, addressed as arg0[-1] */

typedef struct S_81934C5C_0 {
    void * unk_00;
    u8 pad_04[0x8];
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u8 pad_12[0xA];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_28;   /* overlapping accesses */
    u8 pad_2C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_30;   /* overlapping accesses */
    u8 pad_34[0x14];
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_81934C5C_0;   /* arg0 in func_81934C5C */

typedef struct S_81934C5C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_81934C5C_1;   /* temp_v1 in func_81934C5C */

typedef struct S_81934C5C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934C5C_2;   /* temp_v0_3 in func_81934C5C */

typedef struct S_81934C5C_3 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81934C5C_3;   /* temp_s1 in func_81934C5C */

typedef struct S_81934C5C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81934C5C_4;   /* temp_spawn_base in func_81934C5C */

typedef struct S_81934C5C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81934C5C_5;   /* ((S_81934C5C_2 *)temp_v0_3)->unk_08 in func_81934C5C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024678() __attribute__((noreturn));
void func_8002468C() __attribute__((noreturn));
void func_80024724() __attribute__((noreturn));
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
s16 func_800BCB04();
extern M2C_UNK D_80024928;
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;

void func_81934C5C(void *arg0) {
    s32 temp_a0;
    s32 temp_v0_2;
    s16 temp_v1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_state2_x;   /* MATCH pin: retail basic-block layout depends on it */
    s32 temp_state2_dx;
    s32 temp_call_a1;
    s32 temp_call_a0;
    s32 temp_state2_step_x;
    s32 temp_state2_step_x3;
    s32 temp_state2_step_y3;
    s32 temp_state2_delta_y;
    s32 temp_state2_base_y;
    s32 temp_state2_y;
    u16 temp_v0;
    S_81934C5C_3 *temp_s1;
    S_81934C5C_2 *temp_v0_3;
    S_81934C5C_1 *temp_v1;

    temp_v1 = ((S_81934C5C_0 *)arg0)->unk_00;
    ((S_81934C5C_0 *)arg0)->unk_48.s = (u16) (((S_81934C5C_0 *)arg0)->unk_48.s - 1);
    temp_v1->unk_0E = (u16) (temp_v1->unk_0E | 0x8000);
    temp_v1_2 = ((S_81934C5C_0 *)arg0)->unk_4C;
    if (temp_v1_2 == 2) {
        goto block_state2;
    }
    if (temp_v1_2 < 3) {
        if (temp_v1_2 == 0) {
            goto block_state0;
        }
        if (temp_v1_2 == 1) {
            goto block_state1;
        }
        func_80024724();
        return;
    }
    if (temp_v1_2 == 3) {
        goto block_state3;
    }
    if (temp_v1_2 == 0xFF) {
        goto block_state_ff;
    }
    func_80024724();
    return;

block_state0:
    ((S_81934C5C_0 *)arg0)->unk_48.s = 3U;
    ((S_81934C5C_0 *)arg0)->unk_28.at02.v = -4;
    ((S_81934C5C_0 *)arg0)->unk_30.at02.v = 0x10;
    ((S_81934C5C_0 *)arg0)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)arg0)->unk_4C + 1);

block_state1:
    ((S_81934C5C_0 *)arg0)->unk_1C.at00.v = (s32) (((S_81934C5C_0 *)arg0)->unk_1C.at00.v + ((S_81934C5C_0 *)arg0)->unk_28.at00.v);
    temp_a0 = ((S_81934C5C_0 *)arg0)->unk_48.u;
    ((S_81934C5C_0 *)arg0)->unk_24.at00.v = (s32) (((S_81934C5C_0 *)arg0)->unk_24.at00.v + ((S_81934C5C_0 *)arg0)->unk_30.at00.v);
    if (temp_a0 <= 0) {
        func_8002468C(temp_a0);
        return;
    }
    goto block_return;

block_state2:
    temp_state2_x = ((S_81934C5C_0 *)arg0)->unk_1C.at00.v;
    temp_state2_dx = ((S_81934C5C_0 *)arg0)->unk_28.at00.v;
    temp_call_a1 = ((S_81934C5C_0 *)arg0)->unk_20.at02.v;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_a2 = ((S_81934C5C_0 *)arg0)->unk_30.at02.v;
    temp_a3 = ((S_81934C5C_0 *)arg0)->unk_30.at00.v;
    ((S_81934C5C_0 *)arg0)->unk_1C.at00.v = temp_state2_x + temp_state2_dx;
    ASM_CLOBBER("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_state2_step_x = ((S_81934C5C_0 *)arg0)->unk_28.at02.v;
    temp_call_a0 = ((S_81934C5C_0 *)arg0)->unk_1C.at02.v;
    temp_state2_step_x3 = temp_state2_step_x * 3;
    ASM_KEEP(temp_state2_step_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_81934C5C_0 *)arg0)->unk_0C = (u16) (((S_81934C5C_0 *)arg0)->unk_0C + (temp_state2_step_x3 >> 2));
    temp_state2_step_y3 = temp_a2 * 3;
    temp_state2_delta_y = temp_state2_step_y3 >> 2;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_state2_base_y = ((S_81934C5C_0 *)arg0)->unk_10;
    do {
        temp_a2 = ((S_81934C5C_0 *)arg0)->unk_24.at00.v;
    } while (0);
    temp_state2_y = temp_state2_base_y + temp_state2_delta_y;
    temp_a2 += temp_a3;
    ((S_81934C5C_0 *)arg0)->unk_24.at00.v = temp_a2;
    ((S_81934C5C_0 *)arg0)->unk_10 = temp_state2_y;
    temp_v0_2 = func_800BCB04(temp_call_a0, temp_call_a1, -0x400, temp_a3);
    if (temp_v0_2 >= 0x201) {
        if (((S_81934C5C_0 *)arg0)->unk_24.at02.v > 0) {
            goto block_tail_ff;
        }
    }
    if (temp_v0_2 >= ((S_81934C5C_0 *)arg0)->unk_24.at02.v) {
        goto block_return;
    }
    ((S_81934C5C_0 *)arg0)->unk_24.at02.v = temp_v0_2;
    temp_v0_3 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0_3 != NULL) {
        temp_v0_3->unk_10 = &D_80024928;
        temp_v0_3->unk_20 = (void *) ((S_81934C5C_0 *)arg0)->unk_00;
        func_8004491C(temp_v0_3, &D_80045340);
        temp_s1 = temp_v0_3->unk_0C;
        ((S_81934C5C_5 *)(temp_v0_3->unk_08))->unk_00 = (s32) ((S_81934C5C_0 *)arg0)->unk_1C.at00.v;
        ((S_81934C5C_5 *)(temp_v0_3->unk_08))->unk_04 = (s32) ((S_81934C5C_0 *)arg0)->unk_20.at00.v;
        ((S_81934C5C_5 *)(temp_v0_3->unk_08))->unk_08 = (s32) ((S_81934C5C_0 *)arg0)->unk_24.at00.v;
        temp_s1->unk_1E = 0x500;
        temp_s1->unk_1C = 0x500;
        temp_s1->unk_14 = (u16) (temp_s1->unk_14 | 0xC);
        if (func_80069EF8() & 1) {
            M2C_UNK *temp_tail_base = &D_800DEDB0;

            ASM_TAILSLOT_PIN(temp_tail_base);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024678();
            return;
        }
        {
            M2C_UNK *temp_spawn_base;

            ASM_CLOBBER("$2");   /* MATCH pin: retail basic-block layout depends on it */
            temp_spawn_base = &D_800DEE38;
            temp_s1->unk_00 = temp_spawn_base;
            temp_s1->unk_08 = (s32) ((S_81934C5C_4 *)temp_spawn_base)->unk_04;
            temp_s1->unk_04 = 0;
            temp_s1->unk_05 = 0;
        }
    }
    ((S_81934C5C_0 *)arg0)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)arg0)->unk_4C + 1);
    func_80024724();
    return;

block_state3:
    ((S_81934C5C_0 *)arg0)->unk_0C = (u16) (((S_81934C5C_0 *)arg0)->unk_0C + ((s32) (((S_81934C5C_0 *)arg0)->unk_28.at02.v * 3) >> 2));
    temp_v0 = ((S_81934C5C_0 *)arg0)->unk_10 + ((s32) (((S_81934C5C_0 *)arg0)->unk_30.at02.v * 3) >> 2);
    ((S_81934C5C_0 *)arg0)->unk_10 = temp_v0;
    if (((S_81934C5C_0 *)arg0)->unk_24.at02.v < (s16) temp_v0) {
        ((S_81934C5C_0 *)arg0)->unk_10 = (u16) ((S_81934C5C_0 *)arg0)->unk_24.at02.v;
        goto block_tail_ff;
    }
    goto block_return;

block_tail_ff:
    ((S_81934C5C_0 *)arg0)->unk_4C = 0xFF;
    func_80024724();
    return;

block_state_ff:
    ((S_81934C5C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_81934C5C_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;

block_return:
    return;
}
