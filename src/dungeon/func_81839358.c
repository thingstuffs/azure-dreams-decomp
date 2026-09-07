#include "common.h"
#include "m2c_compat.h"

typedef struct S_81839358_0 {
    union { struct { volatile s32 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    union { volatile s32 v; s32 n; } unk_0C;   /* accessed as both */
    union { volatile s32 v; s32 n; } unk_10;   /* accessed as both */
    union { volatile s32 v; s32 n; } unk_14;   /* accessed as both */
} S_81839358_0;   /* arg1 in func_81839358 */

typedef struct S_81839358_1_pre {
    u16 unk_00;
} S_81839358_1_pre;   /* the 0x2 bytes before arg0 in func_81839358, addressed as arg0[-1] */

typedef struct S_81839358_1 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x40];
    u16 unk_48;
    s16 unk_4A;
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_81839358_1;   /* arg0 in func_81839358 */

typedef struct S_81839358_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_81839358_2;   /* temp_v1 in func_81839358 */

typedef struct S_81839358_3 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81839358_3;   /* arg2 in func_81839358 */

typedef struct S_81839358_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81839358_4;   /* &D_800DED28 in func_81839358 */


void func_80024D24(void) __attribute__((noreturn));                         /* extern */
void func_80024D90(void) __attribute__((noreturn));                         /* extern */
void func_80024DCC(void) __attribute__((noreturn));                    /* extern */
void func_8004491C(void *, void *);           /* extern */
void func_800478B8(void *);                 /* extern */
extern M2C_UNK D_80045340;
extern s32 D_800814A0;
extern u8 D_800DEC70[];
extern M2C_UNK D_800DED28;

void func_81839358(void *arg0, void *arg1, void *arg2) {
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 temp_a0_2;
    register s32 temp_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 init_pos;
    s32 init_vel;
    s32 sprite_word;
    s32 state_shift;
    u8 actor_count;
    s32 temp_a0;
    u16 temp_v0;
    u8 temp_v1_3;
    void *temp_v1;

    init_pos = ((S_81839358_0 *)arg1)->unk_00.at00.v;
    init_vel = ((S_81839358_0 *)arg1)->unk_0C.v;
    temp_a0_2 = ((S_81839358_0 *)arg1)->unk_10.v;
    temp_a1 = ((S_81839358_0 *)arg1)->unk_14.v;
    ((S_81839358_0 *)arg1)->unk_00.at00u.v = init_pos + init_vel;
    ((S_81839358_0 *)arg1)->unk_04.at00.v = (s32) (((S_81839358_0 *)arg1)->unk_04.at00.v + temp_a0_2);
    ((S_81839358_0 *)arg1)->unk_08 = (s32) (((S_81839358_0 *)arg1)->unk_08 + temp_a1);
    temp_v1 = ((S_81839358_1 *)arg0)->unk_00;
    ((S_81839358_2 *)temp_v1)->unk_10 = (s32) (((S_81839358_2 *)temp_v1)->unk_10 | 0x8000);
    var_v0 = ((S_81839358_0 *)arg1)->unk_00.at02.v;
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    if ((var_v0 >> 6) == ((S_81839358_1 *)arg0)->unk_04) {
        var_v0_2 = ((S_81839358_0 *)arg1)->unk_04.at02.v;
        if (var_v0_2 < 0) {
            var_v0_2 += 0x3F;
        }
        if ((var_v0_2 >> 6) == ((S_81839358_1 *)arg0)->unk_06) {
            ((S_81839358_0 *)arg1)->unk_14.n = 0;
            ((S_81839358_0 *)arg1)->unk_10.n = 0;
            ((S_81839358_0 *)arg1)->unk_0C.n = 0;
        }
    }
    temp_v1_2 = ((S_81839358_1 *)arg0)->unk_4C.s;
    temp_a0 = ((S_81839358_1 *)arg0)->unk_48 - 1;
    ((S_81839358_1 *)arg0)->unk_48 = temp_a0;
    if (temp_v1_2 == 1) {
        goto state_1;
    }
    if (temp_v1_2 >= 2) {
        goto state_ge_2;
    }
    state_shift = temp_a0 << 0x10;
    if (temp_v1_2 == 0) {
        goto state_0;
    }
    func_80024DCC();
    return;
state_ge_2:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (temp_v1_2 == 2) {
        goto block_27;
    }
    func_80024DCC();
    return;
state_0:
    if (state_shift > 0) {
        return;
    }
    func_8004491C(arg0 - 0x20, &D_80045340);
    ((S_81839358_1 *)arg0)->unk_4C.u = ((S_81839358_1 *)arg0)->unk_4C.u + 1;
    func_80024DCC();
    return;
state_1:
    {
        func_800478B8(arg2);
        if (((S_81839358_3 *)arg2)->unk_14 & 0x6000) {
            ((S_81839358_3 *)arg2)->unk_04 = 0;
            ((S_81839358_3 *)arg2)->unk_05 = 0;
        }
        actor_count = ((S_81839358_3 *)arg2)->unk_0C.at00.v;
        ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        if (((S_81839358_1 *)arg0)->unk_4A >= (s32) actor_count) {
            temp_a0_2 = ((S_81839358_0 *)arg1)->unk_10.n;
            ((S_81839358_0 *)arg1)->unk_0C.n = (s32) (((S_81839358_0 *)arg1)->unk_0C.n * 5);
            ((S_81839358_0 *)arg1)->unk_10.n = (s32) (temp_a0_2 * 5);
            ((S_81839358_0 *)arg1)->unk_14.n = (s32) (((S_81839358_0 *)arg1)->unk_14.n * 8);
            ((S_81839358_3 *)arg2)->unk_1E = 0xC00U;
            ((S_81839358_3 *)arg2)->unk_1C = 0xC00U;
            ((S_81839358_3 *)arg2)->unk_0C.at00u.v = ((S_81839358_3 *)arg2)->unk_0C.at00u.v * 4;
            if (((S_81839358_1 *)arg0)->unk_48 & 1) {
                u8 *dispatch_ptr;
                dispatch_ptr = D_800DEC70;
                ASM_TAILSLOT_PIN(dispatch_ptr);   /* MATCH pin: retail delay-slot contents depend on it */
                func_80024D24();
                return;
            }
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_81839358_3 *)arg2)->unk_00 = &D_800DED28;
            sprite_word = ((S_81839358_4 *)(&D_800DED28))->unk_04;
            ((S_81839358_3 *)arg2)->unk_04 = 0;
            ((S_81839358_3 *)arg2)->unk_05 = 0;
            ((S_81839358_3 *)arg2)->unk_08 = sprite_word;
            ((S_81839358_1 *)arg0)->unk_4C.u = ((S_81839358_1 *)arg0)->unk_4C.u + 1;
            func_80024D90();
            return;
        }
        temp_v0 = ((S_81839358_3 *)arg2)->unk_1E - 0x200;
        ((S_81839358_3 *)arg2)->unk_1E = temp_v0;
        ((S_81839358_3 *)arg2)->unk_1C = temp_v0;
        ((S_81839358_3 *)arg2)->unk_0C.at00.v = (u8) (((S_81839358_3 *)arg2)->unk_0C.at00.v - (u8) ((S_81839358_1 *)arg0)->unk_4A);
        temp_v1_3 = ((S_81839358_3 *)arg2)->unk_0C.at02.v - ((s32) ((u16) ((S_81839358_1 *)arg0)->unk_4A << 0x10) >> 0x12);
        ((S_81839358_3 *)arg2)->unk_0C.at02.v = temp_v1_3;
        ((S_81839358_3 *)arg2)->unk_0C.at01.v = temp_v1_3;
block_27:
        func_800478B8(arg2);
        if (((S_81839358_3 *)arg2)->unk_14 & 0x6000) {
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_81839358_1_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
    }
}
/* MECHANISM: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
