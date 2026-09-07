#include "common.h"
#include "m2c_compat.h"

typedef struct S_8197D468_0_pre {
    u16 unk_00;
} S_8197D468_0_pre;   /* the 0x2 bytes before arg0 in func_8197D468, addressed as arg0[-1] */

typedef struct S_8197D468_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_8197D468_0;   /* arg0 in func_8197D468 */

typedef struct S_8197D468_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8197D468_1;   /* temp_v0 in func_8197D468 */

typedef struct S_8197D468_2 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8197D468_2;   /* arg2 in func_8197D468 */

typedef struct S_8197D468_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8197D468_3;   /* arg1 in func_8197D468 */

typedef struct S_8197D468_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8197D468_4;   /* &D_800DE990 in func_8197D468 */

typedef struct S_8197D468_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8197D468_5;   /* temp_v0_2 in func_8197D468 */

typedef struct S_8197D468_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8197D468_6;   /* temp_s0 in func_8197D468 */

typedef struct S_8197D468_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8197D468_7;   /* D_800DED70 in func_8197D468 */

typedef struct S_8197D468_8 {
    u8 pad_00[0x4C];
    s16 unk_4C;
} S_8197D468_8;   /* temp_v0_4 in func_8197D468 */

typedef struct S_8197D468_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8197D468_9;   /* ((S_8197D468_5 *)temp_v0_2)->unk_08 in func_8197D468 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_8008378A;
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DED70[];
extern s32 D_800814A0;
void func_80025050(void) __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024BB8;
extern M2C_UNK D_800DE990;

void func_8197D468(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s16 temp_v0_5;
    s32 var_s3;
    s32 temp_v0_7;
    s32 random_value_0;
    s32 velocity_0;
    s32 random_value_2;
    s32 velocity_2;
    u16 temp_v0_3;
    u16 temp_v1_2;
    s32 temp_a0_5;
    void *temp_a0_4;
    void *temp_v0_4;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = ((S_8197D468_0 *)arg0)->unk_00;
    ((S_8197D468_1 *)temp_v0)->unk_52 = (u16) (((S_8197D468_1 *)temp_v0)->unk_52 | 0x8000);
    if (((S_8197D468_2 *)arg2)->unk_14 & 0x6000) {
        ((S_8197D468_2 *)arg2)->unk_04 = 0;
        ((S_8197D468_2 *)arg2)->unk_05 = 0;
        ((S_8197D468_2 *)arg2)->unk_14 = (u16) (((S_8197D468_2 *)arg2)->unk_14 & 0x9FFF);
    }
    func_800478B8(arg2);
    temp_v1 = ((S_8197D468_0 *)arg0)->unk_4C.s;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        func_80025050();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (temp_v1 == 2) {
        goto state_2;
    }
    func_80025050();

state_0:
        ((S_8197D468_3 *)arg1)->unk_08.at00.v = (s32) (((S_8197D468_3 *)arg1)->unk_08.at00.v + ((S_8197D468_3 *)arg1)->unk_14);
        random_value_0 = func_80069EF8();
        velocity_0 = ((S_8197D468_3 *)arg1)->unk_14 + 0x1A000;
        velocity_0 += random_value_0 >> 1;
        ((S_8197D468_3 *)arg1)->unk_14 = velocity_0;
        if ((u8) ((S_8197D468_2 *)arg2)->unk_0C.u8 < 0x40) {
            ((S_8197D468_2 *)arg2)->unk_0C.s32 = (s32) ((s32) ((S_8197D468_2 *)arg2)->unk_0C.s32 + 0x40404);
        }
        if (((S_8197D468_3 *)arg1)->unk_14 > 0) {
            ((S_8197D468_2 *)arg2)->unk_00 = &D_800DE990;
            temp_a0_4 = (void *) ((S_8197D468_4 *)(&D_800DE990))->unk_04;
            ASM_KEEP(temp_a0_4);   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v1_2 = ((S_8197D468_2 *)arg2)->unk_14;
            ASM_KEEP(temp_v1_2);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ((S_8197D468_2 *)arg2)->unk_04 = 0;
            ((S_8197D468_2 *)arg2)->unk_05 = 0;
            ((S_8197D468_2 *)arg2)->unk_1E = 0x400U;
            ((S_8197D468_2 *)arg2)->unk_1C = 0x400U;
            ((S_8197D468_2 *)arg2)->unk_10 = 0;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_8197D468_2 *)arg2)->unk_08 = temp_a0_4;
            ((S_8197D468_2 *)arg2)->unk_14 = (u16) (temp_v1_2 | 2);
            ((S_8197D468_0 *)arg0)->unk_48 = (u16) ((func_80069EF8(temp_a0_4) & 3) + 4);
            ((S_8197D468_0 *)arg0)->unk_4C.u = (u16) (((S_8197D468_0 *)arg0)->unk_4C.u + 1);
            func_80025050();
        }
        goto done;

state_1:
        ((S_8197D468_2 *)arg2)->unk_0C.s32 = 0x606060;
        ((S_8197D468_2 *)arg2)->unk_1C = (u16) (((S_8197D468_2 *)arg2)->unk_1C + 0xC8);
        ((S_8197D468_2 *)arg2)->unk_1E = (u16) (((S_8197D468_2 *)arg2)->unk_1E + 0xC8);
        temp_v0_3 = ((S_8197D468_0 *)arg0)->unk_48 - 1;
        ((S_8197D468_0 *)arg0)->unk_48 = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            ((S_8197D468_0 *)arg0)->unk_4C.u = (u16) (((S_8197D468_0 *)arg0)->unk_4C.u + 1);
            func_80025050();
        }
        goto done;

state_2:
        if (((S_8197D468_2 *)arg2)->unk_14 & 0x6000) {
            ((S_8197D468_2 *)arg2)->unk_00 = &D_800DE990;
            temp_v0_4 = (void *) ((S_8197D468_4 *)(&D_800DE990))->unk_04;
            ((S_8197D468_2 *)arg2)->unk_04 = 0;
            ((S_8197D468_2 *)arg2)->unk_05 = 0;
            ((S_8197D468_2 *)arg2)->unk_08 = temp_v0_4;
        }
        ((S_8197D468_3 *)arg1)->unk_08.at00.v = (s32) (((S_8197D468_3 *)arg1)->unk_08.at00.v + ((S_8197D468_3 *)arg1)->unk_14);
        random_value_2 = func_80069EF8();
        velocity_2 = ((S_8197D468_3 *)arg1)->unk_14 + 0x1C000;
        velocity_2 += random_value_2 >> 1;
        ((S_8197D468_3 *)arg1)->unk_14 = velocity_2;
        if ((u8) ((S_8197D468_2 *)arg2)->unk_0C.u8 < 0x80) {
            ((S_8197D468_2 *)arg2)->unk_0C.s32 = (s32) ((s32) ((S_8197D468_2 *)arg2)->unk_0C.s32 + 0x40404);
        }
        temp_v0_5 = func_800BCB04(((S_8197D468_3 *)arg1)->unk_00.at02.v, ((S_8197D468_3 *)arg1)->unk_04.at02.v, (s16) (D_8008378A - 0x80));
        if (((S_8197D468_3 *)arg1)->unk_08.at02.v >= (temp_v0_5 - 0x20)) {
            var_s3 = 4;
            do {
                temp_v0_2 = func_8003FD64(0x312, D_80083498);
                if (temp_v0_2 != NULL) {
                    ((S_8197D468_5 *)temp_v0_2)->unk_10 = &D_80024BB8;
                    func_8004491C(temp_v0_2, D_80045340);
                    temp_s0 = ((S_8197D468_5 *)temp_v0_2)->unk_0C;
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_00 = (s32) (((S_8197D468_3 *)arg1)->unk_00.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_04 = (s32) (((S_8197D468_3 *)arg1)->unk_04.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_08 = (s32) (((S_8197D468_3 *)arg1)->unk_08.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_0C = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_10 = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                    ((S_8197D468_9 *)(((S_8197D468_5 *)temp_v0_2)->unk_08))->unk_14 = (s32) (0 - ((func_80069EF8() & 0x3FF) << 8));
                    temp_a0_5 = 0xC00000;
                       /* MATCH pin: retail immediate-load split depends on it */
                    ((S_8197D468_6 *)temp_s0)->unk_1E = 0xC00;
                    ((S_8197D468_6 *)temp_s0)->unk_1C = 0xC00;
                    ((S_8197D468_6 *)temp_s0)->unk_10 = 0x20;
                    ((S_8197D468_6 *)temp_s0)->unk_00 = D_800DED70;
                    ((S_8197D468_6 *)temp_s0)->unk_14 = (u16) (((S_8197D468_6 *)temp_s0)->unk_14 | 0xC);
                    temp_v0_7 = ((S_8197D468_7 *)D_800DED70)->unk_04;
                    temp_a0_5 |= 0x6060;
                    ((S_8197D468_6 *)temp_s0)->unk_04 = 0;
                    ((S_8197D468_6 *)temp_s0)->unk_05 = 0;
                    ((S_8197D468_6 *)temp_s0)->unk_0C = temp_a0_5;
                    ((S_8197D468_6 *)temp_s0)->unk_08 = temp_v0_7;
                    temp_v0_4 = ((S_8197D468_0 *)arg0)->unk_00;
                    ((S_8197D468_5 *)temp_v0_2)->unk_20 = temp_v0_4;
                    temp_v0_4 = temp_v0_2 + 0x20;
                    ASM_KEEP(temp_v0_4);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    ((S_8197D468_8 *)temp_v0_4)->unk_4C = 0;
                }
                var_s3 -= 1;
            } while (var_s3 >= 0);
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8197D468_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
        }
done:
    return;
}
