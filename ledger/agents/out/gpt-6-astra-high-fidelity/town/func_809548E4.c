/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800218E4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    void * unk_10;
    u8 pad_14[0x18];
    union { s16 s; volatile u16 u; u16 p; } unk_2C;   /* accessed as both */
    union { u16 s; s16 u; } unk_2E;   /* accessed as both */
    u8 pad_30[0xA];
    u16 unk_3A;
    u8 pad_3C[0x8];
    s16 unk_44;
    s16 unk_46;
    u16 unk_48;
    union { u16 s; s16 u; } unk_4A;   /* accessed as both */
} S_800218E4_0;   /* arg0 in func_800218E4 */

typedef struct S_800218E4_1 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800218E4_1;   /* var_v0 in func_800218E4 */

typedef struct S_800218E4_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0xC];
    void * unk_14;
    u8 pad_18[0x8];
    void * unk_20;
} S_800218E4_2;   /* var_a0 in func_800218E4 */

typedef struct S_800218E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800218E4_3;   /* temp_v0 in func_800218E4 */

typedef struct S_800218E4_4 {
    u8 pad_00[0x4];
    union { s32 s; void * u; } unk_04;   /* accessed as both */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_800218E4_4;   /* temp_s0 in func_800218E4 */

typedef struct S_800218E4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x3E];
    s32 unk_48;
    u8 pad_4C[0xC];
    s32 unk_58;
    s32 unk_5C;
} S_800218E4_5;   /* base in func_800218E4 */

typedef struct S_800218E4_6 {
    s32 unk_00;
    s32 unk_04;
} S_800218E4_6;   /* *(void **) var_a0 in func_800218E4 */

typedef struct S_800218E4_7 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800218E4_7;   /* temp_v1_2 in func_800218E4 */

typedef struct S_800218E4_8 {
    u8 pad_00[0x3C];
    s16 unk_3C;
} S_800218E4_8;   /* var_a2 in func_800218E4 */

typedef struct S_800218E4_9 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_9;   /* var_v1_6 in func_800218E4 */

typedef struct S_800218E4_10 {
    u8 pad_00[0x38];
    s16 unk_38;
} S_800218E4_10;   /* temp_v0_5 in func_800218E4 */

typedef struct S_800218E4_11 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_11;   /* var_v1_7 in func_800218E4 */

typedef struct S_800218E4_12 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_12;   /* transition_v0 in func_800218E4 */

typedef struct S_800218E4_13 {
    u8 pad_00[0x42];
    s16 unk_42;
} S_800218E4_13;   /* var_a0_6 in func_800218E4 */

typedef struct S_800218E4_14 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_14;   /* temp_v1_8 in func_800218E4 */

typedef struct S_800218E4_15 {
    s32 unk_00;
} S_800218E4_15;   /* &D_8011315C in func_800218E4 */

typedef struct S_800218E4_16 {
    void * unk_00;
    u8 pad_04[0xC];
    s16 * unk_10;
} S_800218E4_16;   /* save_s5 in func_800218E4 */

typedef struct S_800218E4_17 {
    void * unk_00;
    u8 pad_04[0xC];
    s16 * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_800218E4_17;   /* var_s1 in func_800218E4 */

typedef struct S_800218E4_18 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_18;   /* temp_a1 in func_800218E4 */

typedef struct S_800218E4_19 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800218E4_19;   /* temp_a0_2 in func_800218E4 */

typedef struct S_800218E4_20 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} S_800218E4_20;   /* temp_t3 in func_800218E4 */

typedef struct S_800218E4_21 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800218E4_21;   /* temp_v0_3 in func_800218E4 */

typedef struct S_800218E4_22 {
    void * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
} S_800218E4_22;   /* save_s6 in func_800218E4 */

typedef struct S_800218E4_23 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_23;   /* temp_v1_5 in func_800218E4 */

typedef struct S_800218E4_24 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} S_800218E4_24;   /* temp_t3_2 in func_800218E4 */

typedef struct S_800218E4_25 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800218E4_25;   /* temp_v0_4 in func_800218E4 */

typedef struct S_800218E4_26 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
} S_800218E4_26;   /* var_s1_2 in func_800218E4 */

typedef struct S_800218E4_27 {
    u8 pad_00[0x42];
    u16 unk_42;
} S_800218E4_27;   /* ((S_800218E4_14 *)temp_v1_8)->unk_20 in func_800218E4 */

typedef struct S_800218E4_28 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_28;   /* ((S_800218E4_16 *)save_s5)->unk_00 in func_800218E4 */

typedef struct S_800218E4_29 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_29;   /* ((S_800218E4_17 *)var_s1)->unk_00 in func_800218E4 */


M2C_UNK func_80021120();   /* extern */
s32 func_8002263C(); /* extern */
M2C_UNK func_80023E6C();   /* extern */
M2C_UNK func_80033B78();                     /* extern */
M2C_UNK func_80033B9C();                     /* extern */
short SD_Call(); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();           /* extern */
s32 rand();                      /* extern */
M2C_UNK func_800ABD74();                       /* extern */
s32 func_800B1BEC();       /* extern */
M2C_UNK func_800B1DBC();              /* extern */
extern s32 D_80012D5C[0xB58];
extern u8 D_80022514[0x100];
extern s32 D_80024338[3];
extern u8 D_800834B8[0x100];
extern u8 D_80083780[0x100];
extern s16 D_80113158[8];
extern s32 D_8011315C[0xC58];

typedef struct StackRecord {
    s16 sp10;
    s16 sp12;
    void *sp14;
    s32 sp18;
    s16 sp1C;
    s16 sp1E;
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s16 sp26;
    u8 unused[0x10];
} StackRecord;

void func_800218E4(void *arg0_in, s32 arg1, void *arg2, M2C_UNK arg3) {
    StackRecord stack;
    M2C_UNK var_a3;
    register s32 temp_a1_2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_s2_2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 case4_one ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 temp_t1 ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 temp_v1;
    register s32 temp_v1_4 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 transition_timer;
    register s32 transition_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 transition_a0;
    register s32 collision_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 case8_gold;
    s32 case8_score;
    s32 case8_handle;
    s32 case4_global;
    s32 var_a1_5;
    s32 var_a2_2;
    s32 var_a3_2;
    s16 var_s2_9;
    s32 **var_s0;
    s32 **var_s0_2;
    s32 *temp_a0_3;
    s32 *temp_v1_7;
    S_800218E4_13 *var_a0_6;
    s32 temp_a0;
    s32 payout_amount;
    s32 *payout_score;
    s32 payout_carry;
    s32 *payout_gold;
    s32 temp_a0_6;
    s32 temp_a3;
    s32 temp_ret;
    s32 temp_ret_2;
    register void *temp_v0_8 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 var_a0_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_s2;
    s32 var_s2_10;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s2_4;
    s32 var_s2_5;
    s32 var_s2_6;
    s32 var_s2_7;
    s32 var_s2_8;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 var_t2;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u16 temp_a0_4;
    u16 temp_a0_5;
    u16 temp_a0_7;
    u16 temp_v0_10;
    u16 temp_v0_2;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_9;
    u16 temp_v1_10;
    u16 temp_v1_3;
    u16 temp_v1_9;
    void **var_a0_2;
    S_800218E4_19 *temp_a0_2;
    S_800218E4_18 *temp_a1;
    register S_800218E4_4 *temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800218E4_20 *temp_t3;
    S_800218E4_24 *temp_t3_2;
    S_800218E4_3 *temp_v0;
    void *case0_obj;
    S_800218E4_21 *temp_v0_3;
    S_800218E4_25 *temp_v0_4;
    S_800218E4_10 *temp_v0_5;
    S_800218E4_7 *temp_v1_2;
    register S_800218E4_23 *temp_v1_5 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    S_800218E4_14 *temp_v1_8;
    void *var_a0;
    void *var_a2;
    register void *var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *var_s1_2;
    void *var_s7;
    S_800218E4_16 *save_s5;
    register S_800218E4_22 *save_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    void *var_v0;
    void *var_v1_6;
    void *var_v1_7;
    void *arg0 = arg0_in;
    u8 *base;

    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    temp_v1 = ((S_800218E4_0 *)arg0)->unk_2C.s;
    base = D_800834B8;
    switch (temp_v1) {
    case 0:
        var_s2_4 = 3;
        var_v0 = arg0 + 6;
        do {
            ((S_800218E4_1 *)var_v0)->unk_30 = 0;
            var_s2_4 -= 1;
            var_v0 -= 2;
        } while (var_s2_4 >= 0);
        var_s2_4 = 2;
        var_a1 = 1;
        var_a0 = arg0 + 8;
        ((S_800218E4_0 *)arg0)->unk_46 = -1;
        ((S_800218E4_0 *)arg0)->unk_44 = -1;
        ((S_800218E4_0 *)arg0)->unk_00 = &D_80083780;
        ((S_800218E4_0 *)arg0)->unk_10 = (void *) (base + 0x10);
        do {
            ASM_KEEP(var_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            temp_v0 = ((S_800218E4_2 *)var_a0)->unk_20;
            var_s2_4 -= 1;
            case0_obj = temp_v0;
            ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            temp_s0 = case0_obj + 0x20;
            ((S_800218E4_2 *)var_a0)->unk_04 = (s32) temp_v0->unk_08;
            temp_s0->unk_18 = var_a1;
            temp_s0->unk_04.s = 0;
            temp_s0->unk_16 = 0;
            temp_s0->unk_14 = 0;
            ((S_800218E4_2 *)var_a0)->unk_14 = (void *) (case0_obj + 0x4A);
            var_a0 -= 4;
        } while (var_s2_4 >= 0);
        ((S_800218E4_5 *)base)->unk_08 = 0;
        var_s2_4 = 3;
        var_a3 = 0x10000000;
        var_a2 = arg0 + 6;
        var_a0 = arg0 + 0xC;
        var_a1 = 0x04A00000;
        do {
            ((S_800218E4_6 *)(*(void **) var_a0))->unk_00 = var_a3;
            var_s2_4 -= 1;
            ((S_800218E4_6 *)(*(void **) var_a0))->unk_04 = var_a1;
            temp_v1_2 = *(void **) var_a0;
            var_a0 -= 4;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            transition_v0 = 0xFFC00000;
            var_a1 += transition_v0;
            temp_v1_2->unk_14 = 0;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            temp_v1_2->unk_10 = 0;
            temp_v1_2->unk_0C = 0;
            temp_v1_2->unk_08 = 0;
            ((S_800218E4_8 *)var_a2)->unk_3C = 0;
            var_a2 -= 2;
        } while (var_s2_4 >= 0);
        ((S_800218E4_0 *)arg0)->unk_2C.s = (s16) ((u16) ((S_800218E4_0 *)arg0)->unk_2C.s + 1);
        /* fallthrough */
    case 1:
        temp_v0_2 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            ((S_800218E4_5 *)base)->unk_08 = 1;
            ((S_800218E4_0 *)arg0)->unk_2E.s = 0x20U;
            ((S_800218E4_0 *)arg0)->unk_2C.s = (s16) ((u16) ((S_800218E4_0 *)arg0)->unk_2C.s + 1);
            SD_Call(0x521, var_a1, var_a2, var_a3);
            goto block_67;
        }
        goto block_67;
    case 2:
        if ((s16) ((S_800218E4_0 *)arg0)->unk_2E.s == 0x10) {
            SD_Call(0x700);
            SD_Call(0x702);
            var_s2_4 = 2;
            transition_a0 = 3;
            var_v1_6 = arg0 + 8;
            do {
                temp_v0_5 = ((S_800218E4_9 *)var_v1_6)->unk_20;
                var_v1_6 -= 4;
                var_s2_4 -= 1;
                temp_v0_5->unk_38 = transition_a0;
            } while (var_s2_4 >= 0);
        }
        if ((s16) ((S_800218E4_0 *)arg0)->unk_2E.s < 0x10) {
            var_s2_4 = 3;
            var_s3 = 0xFFF00000;
            do {
                temp_a0_3 = ((s32 **) arg0)[var_s2_4];
                transition_v0 = ((S_800218E4_0 *)arg0)->unk_2E.u;
                temp_v1_4 = *temp_a0_3;
                transition_v0 <<= 0x10;
                temp_v1_4 += var_s3;
                temp_v1_4 += transition_v0;
                *temp_a0_3 = temp_v1_4;
                temp_ret = rand(temp_a0_3);
                if (temp_ret == ((temp_ret / 3) * 3)) {
                    func_800ABD74(((s32 **) arg0)[var_s2_4]);
                }
                var_s2_4 -= 1;
            } while (var_s2_4 >= 0);
        }
        temp_v0_6 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            ((S_800218E4_5 *)base)->unk_08 = 2;
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x10;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
            goto block_advance_loaded;
        }
        goto block_67;
    case 3:
        var_s2_4 = 3;
        do {
            temp_v1_7 = ((s32 **) arg0)[var_s2_4];
            *temp_v1_7 += 0xFFF00000;
            temp_ret_2 = rand();
            if (temp_ret_2 == ((temp_ret_2 / 3) * 3)) {
                func_800ABD74(((s32 **) arg0)[var_s2_4]);
            }
            var_s2_4 -= 1;
        } while (var_s2_4 >= 0);
        temp_v0_7 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_v0_7;
        if ((temp_v0_7 << 0x10) <= 0) {
            ((S_800218E4_5 *)base)->unk_08 = 3;
            var_s2_4 = 2;
            var_a1_5 = 0x100;
            var_a0_6 = (void *)0xC0000;
            var_v1_7 = arg0 + 8;
            do {
                temp_v0_8 = ((S_800218E4_11 *)var_v1_7)->unk_20;
                var_v1_7 -= 4;
                temp_s0 = temp_v0_8 + 0x20;
                temp_s0->unk_22 = var_s2_4;
                var_s2_4 -= 1;
                temp_s0->unk_18 = var_a1_5;
                temp_s0->unk_1C = 0;
                temp_s0->unk_04.u = var_a0_6;
            } while (var_s2_4 >= 0);
            var_s2_4 = 0xA;
            do {
                var_s2_4 -= 1;
                transition_v0 = rand(var_a0_6, var_a1_5);
                var_s3 = transition_v0 / 3;
                var_s3 = transition_v0 - (var_s3 * 3);
                transition_v0 = rand();
                var_t2 = transition_v0 / 3;
                var_t2 = transition_v0 - (var_t2 * 3);
                transition_v0 = var_s3 * 4;
                transition_v0 += (s32) arg0;
                temp_v1_4 = var_t2 * 4;
                temp_v1_4 += (s32) arg0;
                var_a0_6 = ((S_800218E4_12 *)transition_v0)->unk_20;
                temp_v1_8 = temp_v1_4;
                var_a1_5 = var_a0_6->unk_42;
                var_a0_6->unk_42 = (s16) ((S_800218E4_27 *)(temp_v1_8->unk_20))->unk_42;
                ((S_800218E4_27 *)(temp_v1_8->unk_20))->unk_42 = (u16) var_a1_5;
            } while (var_s2_4 >= 0);
            SD_Call(0x1702, var_a1_5);
            goto block_advance;
        }
        goto block_67;
    case 4:
        ((S_800218E4_0 *)arg0)->unk_2E.s = (u16) (((S_800218E4_0 *)arg0)->unk_2E.s + 1);
        if (((S_800218E4_0 *)arg0)->unk_46 >= 0) {
            if (((S_800218E4_0 *)arg0)->unk_44 != 0) {
                func_80033B78(0x58F);
            } else {
                func_80033B9C(0x58F);
            }
            temp_s2_2 = ((S_800218E4_0 *)arg0)->unk_44;
            if (((S_800218E4_0 *)arg0)->unk_46 < temp_s2_2) {
                ((S_800218E4_0 *)arg0)->unk_44 = (s16) (u16) ((S_800218E4_0 *)arg0)->unk_46;
                ((S_800218E4_0 *)arg0)->unk_46 = temp_s2_2;
            }
            case4_one = 1;
            collision_a0 = ((S_800218E4_0 *)arg0)->unk_44;
            temp_v1_4 = ((S_800218E4_0 *)arg0)->unk_46;
            case4_global = D_80113158[0];
            collision_a0 = case4_one << collision_a0;
            temp_v1_4 = case4_one << temp_v1_4;
            temp_s2_2 = collision_a0 + temp_v1_4;
            if (case4_global != temp_s2_2) {
                ((S_800218E4_15 *)(&D_8011315C))->unk_00 = 0;
            }
            ((S_800218E4_0 *)arg0)->unk_2E.s = 0x40U;
            ((S_800218E4_0 *)arg0)->unk_4A.s = 0x400U;
            ((S_800218E4_0 *)arg0)->unk_48 = 0U;
            stack.sp1C = 0x28;
            stack.sp1E = 0x58;
            stack.sp20 = 0xF0;
            stack.sp22 = 0x50;
            stack.sp24 = 2;
            stack.sp26 = case4_one;
            stack.sp18 = 0;
            stack.sp10 = 0;
            stack.sp12 = 8;
            stack.sp14 = arg0;
            func_80021120(&D_80022514, &stack, 1);
            goto block_advance;
        }
        goto block_67;
    case 5:
        transition_timer = ((S_800218E4_0 *)arg0)->unk_48;
        transition_v0 = ((S_800218E4_0 *)arg0)->unk_2E.s;
        transition_timer += 0x12C;
        transition_v0 <<= 1;
        transition_timer += transition_v0;
        transition_v0 = ((S_800218E4_0 *)arg0)->unk_4A.s;
        ((S_800218E4_0 *)arg0)->unk_48 = transition_timer;
        transition_timer = ((S_800218E4_0 *)arg0)->unk_2E.s;
        transition_v0 += 0x10;
        transition_timer -= 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
        transition_timer <<= 0x10;
        ((S_800218E4_0 *)arg0)->unk_4A.s = transition_v0;
        if (transition_timer <= 0) {
            if (D_80113158[0] != 0) {
                D_80024338[0] = func_800B1BEC(0, -0x50, 0x40);
            }
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x10;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
            goto block_advance_loaded;
        }
        goto block_67;
    case 6:
        transition_v0 = 0x10;
        transition_timer = ((S_800218E4_0 *)arg0)->unk_48;
        transition_a0 = ((S_800218E4_0 *)arg0)->unk_2E.s;
        transition_timer += 0x12C;
        transition_v0 -= transition_a0;
        transition_v0 <<= 3;
        transition_timer -= transition_v0;
        ((S_800218E4_0 *)arg0)->unk_48 = transition_timer;
        transition_timer = transition_a0;
        ASM_KEEP(transition_timer);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        transition_v0 = ((S_800218E4_0 *)arg0)->unk_4A.s;
        transition_timer -= 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
        transition_timer <<= 0x10;
        transition_v0 += 0x15E;
        ((S_800218E4_0 *)arg0)->unk_4A.s = transition_v0;
        if (transition_timer <= 0) {
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x21;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
            goto block_advance_loaded;
        }
        goto block_67;
    case 7:
        ((S_800218E4_0 *)arg0)->unk_48 = (u16) (((S_800218E4_0 *)arg0)->unk_48 + 0xA0);
        temp_a0_5 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_a0_5;
        temp_a0_6 = temp_a0_5 << 0x10;
        ((S_800218E4_0 *)arg0)->unk_4A.s = (u16) (((S_800218E4_0 *)arg0)->unk_4A.s + ((s32) (0x1EDC - (s16) ((S_800218E4_0 *)arg0)->unk_4A.s) >> 1));
        if (temp_a0_6 <= 0) {
            ((S_800218E4_0 *)arg0)->unk_48 = 0U;
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.u;
            transition_timer = 0x10;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
            goto block_advance_loaded;
        }
        goto block_67;
    case 8:
        transition_timer = 0x2001;
        transition_v0 = ((S_800218E4_0 *)arg0)->unk_4A.u;
        transition_a0 = ((S_800218E4_0 *)arg0)->unk_2E.s;
        transition_timer -= transition_v0;
        transition_timer >>= 1;
        transition_v0 = ((S_800218E4_0 *)arg0)->unk_4A.s;
        transition_a0 -= 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = transition_a0;
        transition_a0 <<= 0x10;
        transition_v0 += transition_timer;
        ((S_800218E4_0 *)arg0)->unk_4A.s = transition_v0;
        if (transition_a0 <= 0) {
            if (D_80113158[0] != 0) {
                case8_gold = D_80012D5C[0];
                case8_score = D_8011315C[0];
                case8_handle = D_80024338[0];
                case8_gold += case8_score;
                D_80012D5C[0] = case8_gold;
                func_800B1DBC(case8_handle);
            }
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x8F;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)arg0)->unk_2E.s = transition_timer;
            goto block_advance_loaded;
        }
        goto block_67;
    case 9:
        if ((s16) ((S_800218E4_0 *)arg0)->unk_2E.s == 0x64) {
            SD_Call(0x702);
        }
        temp_v0_9 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_v0_9;
        if ((temp_v0_9 << 0x10) <= 0) {
            SD_Call(0x72);
            ((S_800218E4_0 *)arg0)->unk_2E.s = 0x1EU;
            ((S_800218E4_0 *)arg0)->unk_3A = (u16) (((S_800218E4_0 *)arg0)->unk_3A | 0x8000);
            ((S_800218E4_0 *)arg0)->unk_2C.p = (u16) (((S_800218E4_0 *)arg0)->unk_2C.p + 1);
            goto block_67;
        }
        goto block_67;
    case 10:
        temp_v0_10 = ((S_800218E4_0 *)arg0)->unk_2E.s - 1;
        ((S_800218E4_0 *)arg0)->unk_2E.s = temp_v0_10;
        if ((temp_v0_10 << 0x10) <= 0) {
            ((S_800218E4_5 *)base)->unk_08 = 4;
block_advance:
            transition_v0 = ((S_800218E4_0 *)arg0)->unk_2C.p;
block_advance_loaded:
            ((S_800218E4_0 *)arg0)->unk_2C.s = (s16) (transition_v0 + 1);
        }
        goto block_67;
    default:
block_67:
        if ((u32) ((u16) ((S_800218E4_0 *)arg0)->unk_2C.s - 6) < 3U) {
            payout_amount = D_8011315C[0];
            if (payout_amount >= 0x3E8) {
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x3E8;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x3E8;
                *payout_gold = payout_carry;
            } else {
                if (payout_amount < 0x64) {
                    goto block_73;
                }
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x64;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x64;
                *payout_gold = payout_carry;
            }
            goto block_73;
        }
block_73:
        temp_v1_3 = (u16) ((S_800218E4_0 *)arg0)->unk_2C.s;
        if ((u32) (temp_v1_3 - 5) < 5U) {
            transition_v0 = (s16) temp_v1_3;
            temp_s2_2 = transition_v0 < 9;
            func_80023E6C(0x50, ((S_800218E4_0 *)arg0)->unk_44, arg0, temp_s2_2);
            func_80023E6C(-0xF0, ((S_800218E4_0 *)arg0)->unk_46, arg0, temp_s2_2);
            func_80023E6C(0xA0, 4, arg0, temp_s2_2);
            func_80023E6C(-0xA0, 4, arg0, temp_s2_2);
        }
        var_s2_4 = 0;
        if (((S_800218E4_0 *)arg0)->unk_2C.s >= 4) {
            var_s7 = arg0;
loop_77:
            var_s3 = var_s2_4 + 1;
            if (var_s3 < 4) {
                transition_v0 = var_s3 * 4;
                save_s5 = var_s7;
                save_s6 = var_s7;
                var_s1 = (void *)(transition_v0 + (s32) arg0);
loop_79:
                temp_a1 = save_s5->unk_00;
                temp_a0_2 = ((S_800218E4_17 *)var_s1)->unk_00;
                transition_v0 = temp_a1->unk_0A;
                temp_v1_4 = temp_a0_2->unk_0A;
                transition_v0 -= temp_v1_4;
                if (transition_v0 < 0) {
                    transition_v0 = 0 - transition_v0;
                }
                if (transition_v0 < 0x40) {
                    temp_v1_4 = temp_a1->unk_02;
                    transition_v0 = temp_a0_2->unk_02;
                    collision_a0 = temp_a0_2->unk_06;
                    temp_v1_4 -= transition_v0;
                    transition_v0 = temp_a1->unk_06;
                    if (temp_v1_4 < 0) {
                        temp_v1_4 = 0 - temp_v1_4;
                    }
                    transition_v0 -= collision_a0;
                    if (transition_v0 < 0) {
                        transition_v0 = 0 - transition_v0;
                    }
                    temp_v1_4 += transition_v0;
                    if (temp_v1_4 < 0x38) {
                        transition_v0 = 0x3FFFF;
                        ASM_KEEP(transition_v0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        temp_v1_4 = temp_a1->unk_0C;
                        collision_a0 = temp_a1->unk_10;
                        if (temp_v1_4 < 0) {
                            temp_v1_4 = 0 - temp_v1_4;
                        }
                        if (collision_a0 < 0) {
                            collision_a0 = 0 - collision_a0;
                        }
                        temp_v1_4 += collision_a0;
                        if (temp_v1_4 <= transition_v0) {
                            ((S_800218E4_28 *)(save_s5->unk_00))->unk_0C = (s32) (func_80064584(*save_s5->unk_10, temp_a1) << 6);
                            ((S_800218E4_28 *)(save_s5->unk_00))->unk_10 = (s32) (func_800644B8(*save_s5->unk_10) << 6);
                        }
                        temp_t3 = save_s5->unk_00;
                        temp_v0_3 = ((S_800218E4_17 *)var_s1)->unk_00;
                        temp_a1_2 = temp_t3->unk_02;
                        temp_t0 = temp_t3->unk_10.at02.v;
                        temp_t1 = temp_v0_3->unk_02;
                        temp_v1_4 = temp_t3->unk_06;
                        var_a2_2 = temp_t3->unk_0C.at02.v;
                        var_a3_2 = temp_v0_3->unk_06;
                        collision_a0 = (temp_a1_2 + temp_t0) - temp_t1;
                        if (collision_a0 < 0) {
                            collision_a0 = 0 - collision_a0;
                        }
                        ASM_KEEP(collision_a0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        var_v0_4 = (temp_v1_4 - var_a2_2) - var_a3_2;
                        if (var_v0_4 < 0) {
                            var_v0_4 = 0 - var_v0_4;
                        }
                        ASM_KEEP(var_v0_4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        var_t2 = collision_a0 + var_v0_4;
                        ASM_KEEP(var_t2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        var_a1_2 = (temp_a1_2 - temp_t0) - temp_t1;
                        if (var_a1_2 < 0) {
                            var_a1_2 = 0 - var_a1_2;
                        }
                        var_v1_3 = (temp_v1_4 + var_a2_2) - var_a3_2;
                        if (var_v1_3 < 0) {
                            var_v1_3 = 0 - var_v1_3;
                        }
                        temp_a1_2 = var_a1_2 + var_v1_3;
                        transition_v0 = temp_a1_2 < var_t2;
                        if (transition_v0) {
                            transition_v0 = temp_t3->unk_0C.at00.v;
                            var_t2 = temp_t3->unk_10.at00.v;
                            var_a1_3 = 0 - transition_v0;
                        } else {
                            transition_v0 = temp_t3->unk_10.at00.v;
                            var_a1_3 = temp_t3->unk_0C.at00.v;
                            var_t2 = 0 - transition_v0;
                        }
                        collision_a0 = 0x30000;
                        if (var_s2_4 == 0) {
                            goto block_base_collision;
                        }
                            transition_v0 = save_s6->unk_1C;
                            temp_s0 = transition_v0 + 0x20;
                            temp_s0->unk_0C = (s32) (temp_s0->unk_0C + var_t2);
                            temp_s0->unk_10 = (s32) (temp_s0->unk_10 + var_a1_3);
                            temp_v1_5 = ((S_800218E4_17 *)var_s1)->unk_00;
                            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                            collision_a0 |= 0xFFFF;
                            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                            var_v0_5 = temp_v1_5->unk_0C;
                            var_v1_4 = temp_v1_5->unk_10;
                            if (var_v0_5 < 0) {
                                var_v0_5 = 0 - var_v0_5;
                            }
                            if (var_v1_4 < 0) {
                                var_v1_4 = 0 - var_v1_4;
                            }
                            if ((var_v0_5 + var_v1_4) <= collision_a0) {
                                ((S_800218E4_29 *)(((S_800218E4_17 *)var_s1)->unk_00))->unk_0C = (s32) (func_80064584(*((S_800218E4_17 *)var_s1)->unk_10, (void *) var_a1_3, var_a2_2, var_a3_2) << 6);
                                ((S_800218E4_29 *)(((S_800218E4_17 *)var_s1)->unk_00))->unk_10 = (s32) (func_800644B8(*((S_800218E4_17 *)var_s1)->unk_10) << 6);
                            }
                            temp_t3_2 = ((S_800218E4_17 *)var_s1)->unk_00;
                            temp_v0_4 = save_s6->unk_00;
                            temp_a1_2 = temp_t3_2->unk_02;
                            temp_t0 = temp_t3_2->unk_10.at02.v;
                            temp_t1 = temp_v0_4->unk_02;
                            temp_v1_4 = temp_t3_2->unk_06;
                            var_a2_2 = temp_t3_2->unk_0C.at02.v;
                            var_a3_2 = temp_v0_4->unk_06;
                            collision_a0 = (temp_a1_2 + temp_t0) - temp_t1;
                            if (collision_a0 < 0) {
                                collision_a0 = 0 - collision_a0;
                            }
                            ASM_KEEP(collision_a0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            var_v0_6 = (temp_v1_4 - var_a2_2) - var_a3_2;
                            if (var_v0_6 < 0) {
                                var_v0_6 = 0 - var_v0_6;
                            }
                            ASM_KEEP(var_v0_6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            var_t2 = collision_a0 + var_v0_6;
                            ASM_KEEP(var_t2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            var_a1_4 = (temp_a1_2 - temp_t0) - temp_t1;
                            if (var_a1_4 < 0) {
                                var_a1_4 = 0 - var_a1_4;
                            }
                            var_v1_5 = (temp_v1_4 + var_a2_2) - var_a3_2;
                            if (var_v1_5 < 0) {
                                var_v1_5 = 0 - var_v1_5;
                            }
                            temp_a1_2 = var_a1_4 + var_v1_5;
                            transition_v0 = temp_a1_2 < var_t2;
                            if (transition_v0) {
                                transition_v0 = temp_t3_2->unk_0C.at00.v;
                                var_t2 = temp_t3_2->unk_10.at00.v;
                                var_a1_3 = 0 - transition_v0;
                            } else {
                                transition_v0 = temp_t3_2->unk_10.at00.v;
                                var_a1_3 = temp_t3_2->unk_0C.at00.v;
                                var_t2 = 0 - transition_v0;
                            }
                            if (var_s3 != 0) {
                                goto block_object_collision;
                            }
block_base_collision:
                            ASM_KEEP(collision_a0); /* MATCH: retain the collision threshold across the base-object arm. */
                            ((S_800218E4_5 *)base)->unk_58 = (s32) (((S_800218E4_5 *)base)->unk_58 + var_t2);
                            ((S_800218E4_5 *)base)->unk_5C = (s32) (((S_800218E4_5 *)base)->unk_5C + var_a1_3);
                            goto block_127;
block_object_collision:
                            transition_v0 = ((S_800218E4_17 *)var_s1)->unk_1C;
                            temp_s0 = transition_v0 + 0x20;
                            temp_s0->unk_0C = (s32) (temp_s0->unk_0C + var_t2);
                            temp_s0->unk_10 = (s32) (temp_s0->unk_10 + var_a1_3);
                    }
                    goto block_126;
                }
block_126:
                var_s3 += 1;
                var_s1 += 4;
                if (var_s3 >= 4) {
                    goto block_127;
                }
                goto loop_79;
            }
block_127:
            var_s2_4 += 1;
            var_s7 += 4;
            if (var_s2_4 >= 3) {
                if (func_8002263C(((S_800218E4_0 *)arg0)->unk_00, arg0 + 0x3C, base + 0x58, base + 0x5C) != 0) {
                    ((S_800218E4_5 *)base)->unk_48 = 0;
                }
                var_s2_5 = 1;
                var_s1_2 = arg0 + 4;
                var_s3_2 = 0x3E;
                do {
                    temp_a3 = ((S_800218E4_26 *)var_s1_2)->unk_1C;
                    temp_s0 = temp_a3 + 0x20;
                    if (func_8002263C(((S_800218E4_26 *)var_s1_2)->unk_00, arg0 + var_s3_2, temp_a3 + 0x2C, temp_a3 + 0x30) != 0) {
                        temp_s0->unk_04.s = 0;
                    }
                    var_s1_2 += 4;
                    var_s2_5 += 1;
                    var_s3_2 += 2;
                } while (var_s2_5 < 4);
            } else {
                goto loop_77;
            }
        } else {
            return;
        }
        break;

    }
}
