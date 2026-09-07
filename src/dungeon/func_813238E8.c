/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void func_800353F4(void *);                   /* extern */
void func_80047738(void *, u8, s8);              /* extern */
void func_800478B8(void *);                      /* extern */
void func_800A020C(s32, void *);                 /* extern */
void func_800A1D4C(void *, s32);             /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
void func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
void func_8016A908(void *);                         /* extern */
void func_8016B518(void) __attribute__((noreturn)); /* extern */
void func_8016B564(void) __attribute__((noreturn)); /* extern */
void func_8016B588(void) __attribute__((noreturn)); /* extern */
void func_8016B5F4(void) __attribute__((noreturn)); /* extern */
void func_8016B68C(void) __attribute__((noreturn)); /* extern */
void func_8016B6A4(void) __attribute__((noreturn)); /* extern */
void func_8016B724(void) __attribute__((noreturn)); /* extern */
void func_8016B748() __attribute__((noreturn)); /* extern */
extern u8 D_80013610[0x3612];
extern s16 D_80013714[5];
extern u8 D_8006CCF8[256];
extern s32 D_800814A0[3];
extern s16 D_80083228[5];
extern u8 D_80083460[0x100];
extern u16 D_80083462[5];
extern u32 D_800835E4[64];
extern u8 *D_800E3D7C[3];
extern u8 D_800F927E[16];
extern void D_8016B778(void);
extern void (*D_80174728[256])(void *, void *, void *, void *);


typedef struct S_8016B0E8_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x6];
    u32 unk_18;
    u8 pad_1C[0x70];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    s8 unk_9D;
    u8 pad_9E[0x6];
    void * unk_A4;
    u8 pad_A8[0x8];
    union { u8 n; volatile u8 v; } unk_B0;   /* accessed as both */
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
} S_8016B0E8_0;   /* arg0 in func_8016B0E8 */

typedef struct S_8016B0E8_1 {
    u8 pad_00[0x3610];
    u8 unk_3610;
    u8 unk_3611;
} S_8016B0E8_1;   /* page_8001 in func_8016B0E8 */

typedef struct S_8016B0E8_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    volatile s32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8016B0E8_2;   /* obj in func_8016B0E8 */

typedef struct S_8016B0E8_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
} S_8016B0E8_3;   /* state_83460 in func_8016B0E8 */

typedef struct S_8016B0E8_4 {
    u8 pad_00[0x3D7C];
    s32 unk_3D7C;
} S_8016B0E8_4;   /* page_e in func_8016B0E8 */

typedef struct S_8016B0E8_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_5;   /* entry_base in func_8016B0E8 */

typedef struct S_8016B0E8_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016B0E8_6;   /* temp_v1_2 in func_8016B0E8 */

typedef struct S_8016B0E8_7 {
    s32 unk_00;
} S_8016B0E8_7;   /* &D_800E3D7C in func_8016B0E8 */

typedef struct S_8016B0E8_8 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016B0E8_8;   /* var_a0 in func_8016B0E8 */

typedef struct S_8016B0E8_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016B0E8_9_pre;   /* the 0x14 bytes before temp_v0_2 in func_8016B0E8, addressed as temp_v0_2[-1] */

typedef struct S_8016B0E8_10 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016B0E8_10;   /* temp_v1_3 in func_8016B0E8 */

typedef struct S_8016B0E8_11 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016B0E8_11;   /* late_state_83460 in func_8016B0E8 */

typedef struct S_8016B0E8_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8016B0E8_12;   /* temp_v1_4 in func_8016B0E8 */

typedef struct S_8016B0E8_13 {
    u8 pad_00[0x3462];
    u16 unk_3462;
} S_8016B0E8_13;   /* var_v0_2 in func_8016B0E8 */

typedef struct S_8016B0E8_14 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    s32 unk_2C;
} S_8016B0E8_14;   /* arg2 in func_8016B0E8 */

typedef struct S_8016B0E8_15 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016B0E8_15;   /* arg1 in func_8016B0E8 */

typedef struct S_8016B0E8_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_16;   /* (temp_s1 + ((S_8016B0E8_4 *)page_e)->unk_3D7C) in func_8016B0E8 */

void func_8016B0E8(void *arg0, void *arg1, void *arg2) {
    register M2C_UNK (*temp_v0_4)(void *, void *, void *, void *);
    register M2C_UNK (*temp_v1_5)(void *, void *, void *, void *);
    register s16 temp_a2;
    register s32 temp_s0_2;
    register s32 direction_index ASM_REG("$3");   /* MATCH pin: retail basic-block layout depends on it */
    register s32 prior_direction;
    s16 temp_v0_6;
    s16 height_delta;
    register s32 temp_a0_2;
    register s32 temp_a0_3;
    register s32 temp_a1;
    s32 motion_position;
    s32 motion_delta;
    u16 motion_flags;
    register s32 temp_s1 ASM_REG("$17");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 temp_v0;
    register u8 * temp_v0_5;
    register s32 temp_v1_7;
    s32 var_s0;
    register s32 var_s0_2 ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register u32 var_v0;
    u16 tail_flag;
    register s16 temp_s0;
    u16 *var_v0_2;
    register u16 temp_a0_4;
    u16 temp_v1_6;
    u16 var_v0_3;
    u32 tail_predicate;
    register u32 temp_v1;
    register u32 var_v1;
    register u8 temp_v0_3;
    register u32 *base_835e4;
    register u32 *limit_base;
    register u32 *loop_base;
    register u8 *state_83460;
    register u8 *late_state_83460;
    u8 *message;
    register void *entry_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register void *temp_v0_2;
    register void *temp_v1_2;
    register void *temp_v1_3;
    register void *temp_v1_4;
    register void *var_a0;
    S_8016B0E8_1 *page_8001;
    void *reg_arg0 = arg0;
    void *reg_arg1 = arg1;
    register void *reg_arg2 ASM_REG("$21") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    register void *obj ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *page_e ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s32 high_bit;
#define arg0 reg_arg0
#define arg1 reg_arg1
#define arg2 reg_arg2

    obj = arg0;
    if (((S_8016B0E8_0 *)arg0)->unk_18 == 0) {
        page_8001 = (void *)0x80010000;
        temp_v0 = page_8001->unk_3611 | (page_8001->unk_3610 << 8);
        var_v1 = (u32) temp_v0 >> 2;
        if (temp_v0 < 0) {
            var_v1 = (u32) (temp_v0 + 3) >> 2;
        }
        if (var_v1 < 0x1AU) {
            var_v0 = var_v1 & 0xFFFF;
        } else {
            var_v1 = 0x19;
            ASM_KEEP_NV(var_v1);   /* MATCH pin: retail delay-slot fill depends on it */
            var_v0 = var_v1 & 0xFFFF;
        }
        base_835e4 = D_800835E4;
        limit_base = base_835e4 + 1;
        temp_v1 = base_835e4[var_v0] + 1;
        ((S_8016B0E8_0 *)arg0)->unk_18 = temp_v1;
        if (temp_v1 >= (u32) limit_base[((S_8016B0E8_0 *)arg0)->unk_11]) {
            loop_base = limit_base;
            do {
                func_800A1D4C(obj, 0);
            } while (!((u32) loop_base[((S_8016B0E8_2 *)obj)->unk_11] > (u32) ((S_8016B0E8_2 *)obj)->unk_18));
        }
    }
    if (((S_8016B0E8_0 *)arg0)->unk_B4 != 0) {
        state_83460 = D_80083460;
        if ((((S_8016B0E8_3 *)state_83460)->unk_0C != 0) || (((S_8016B0E8_3 *)state_83460)->unk_0A != 1)) {
            goto block_return;
        }
        if (((S_8016B0E8_0 *)arg0)->unk_B4 == ((S_8016B0E8_3 *)state_83460)->unk_0A) {
            message = D_800F927E;
            ASM_KEEP(message);   /* MATCH pin: retail schedule: same instructions, different order without it */
            var_s0 = 0;
            page_e = (u8 *)0x800E0000;
            (*(s16 *)D_80013714) = (s16) ((*(u16 *)D_80013714) | 8);
            high_bit = 0x80000000;
            func_800353F4(message);
            ((S_8016B0E8_2 *)obj)->unk_6D = 0U;
            ((S_8016B0E8_0 *)arg0)->unk_9B = 0;
            ((S_8016B0E8_0 *)arg0)->unk_B4 = 0U;
            do {
                temp_s1 = var_s0 * 4;
                temp_a0_2 = ((S_8016B0E8_16 *)((temp_s1 + ((S_8016B0E8_4 *)page_e)->unk_3D7C)))->unk_AC;
                if (temp_a0_2 != 0) {
                    func_8016A908(temp_a0_2);
                    entry_base = (void *)(temp_s1 + ((S_8016B0E8_4 *)page_e)->unk_3D7C);
                    temp_v1_2 = ((S_8016B0E8_5 *)entry_base)->unk_AC - 0x20;
                    ((S_8016B0E8_6 *)temp_v1_2)->unk_10 = (s32) (((S_8016B0E8_6 *)temp_v1_2)->unk_10 | high_bit);
                }
                var_s0 += 1;
            } while (var_s0 < 2);
        }
    }
block_16:
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        if ((*(u16 *)D_80013714) & 8) {
            var_s0_2 = 1;
            var_a0 = ((S_8016B0E8_7 *)(&D_800E3D7C))->unk_00 + 4;
            do {
                temp_v0_2 = ((S_8016B0E8_8 *)var_a0)->unk_AC;
                if (temp_v0_2 != NULL) {
                    temp_v1_3 = ((S_8016B0E8_9_pre *)temp_v0_2)[-1].unk_00;
                    ((S_8016B0E8_10 *)temp_v1_3)->unk_14 = (u16) (((S_8016B0E8_10 *)temp_v1_3)->unk_14 & 0xFFBF);
                }
                var_s0_2 -= 1;
                var_a0 -= 4;
            } while (var_s0_2 >= 0);
        }
        if (((S_8016B0E8_0 *)arg0)->unk_B0.n != 0) {
            temp_v0_3 = ((S_8016B0E8_0 *)arg0)->unk_B1 - 1;
            ((S_8016B0E8_0 *)arg0)->unk_B1 = temp_v0_3;
            if (!(temp_v0_3 & 0xFF)) {
                ((S_8016B0E8_2 *)obj)->unk_14 = (s32) (((S_8016B0E8_2 *)obj)->unk_14 & 0xFFEFFFFF);
                ((S_8016B0E8_0 *)arg0)->unk_B0.v = 0U;
                late_state_83460 = D_80083460;
                ((S_8016B0E8_11 *)late_state_83460)->unk_0A = (s16) ((u16) ((S_8016B0E8_11 *)late_state_83460)->unk_0A - 1);
                temp_v1_4 = ((S_8016B0E8_0 *)arg0)->unk_A4;
                ((S_8016B0E8_12 *)temp_v1_4)->unk_1E = (u16) (((S_8016B0E8_12 *)temp_v1_4)->unk_1E | 0x8000);
                D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            }
        }
        var_v0_2 = (u16 *)0x80080000;
        ASM_KEEP_NV(var_v0_2);   /* MATCH pin: retail keeps a computation the compiler would drop */
        if (((S_8016B0E8_13 *)var_v0_2)->unk_3462 & 0x2000) {
            temp_v1_5 = ((S_8016B0E8_0 *)arg0)->unk_8C;
            if (temp_v1_5 == &D_8016B778) {
                temp_v1_5(arg0, arg1, arg2, obj);
                func_8016B748();
                return;
            }
            ((S_8016B0E8_2 *)obj)->unk_71 = (u8) (((S_8016B0E8_2 *)obj)->unk_71 & 0x7F);
            func_8016B748(arg0);
            return;
        }
        temp_s0 = (s8) ((S_8016B0E8_2 *)obj)->unk_6D;
        if (func_800A9E70(arg0, arg1, arg2, obj) == 0) {
            temp_v0_4 = ((S_8016B0E8_0 *)arg0)->unk_8C;
            if (temp_v0_4 != NULL) {
                temp_v0_4(arg0, arg1, arg2, obj);
            }
            D_80174728[((S_8016B0E8_0 *)arg0)->unk_9A](arg0, arg1, arg2, obj);
            if ((s16) temp_s0 != (s8) ((S_8016B0E8_2 *)obj)->unk_6D) {
                func_800AA36C(arg0, arg1, arg2, obj);
            }
            temp_v1_6 = ((S_8016B0E8_14 *)arg2)->unk_14.n;
            tail_predicate = temp_v1_6 & 0x8000;
            if (!tail_predicate) {
                temp_s0_2 = ((s32) (D_80083228[0] + ((S_8016B0E8_2 *)obj)->unk_2A + 0x100) >> 9) & 7;
                prior_direction = ((S_8016B0E8_0 *)arg0)->unk_94;
                ASM_USE_NV(prior_direction);   /* MATCH pin: retail basic-block layout depends on it */
                direction_index = temp_s0_2;
                ASM_KEEP_NV(direction_index);   /* MATCH pin: retail register colouring depends on it */
                temp_s1 = temp_s0_2;
                if (prior_direction != direction_index) {
                    temp_v0_5 = ((S_8016B0E8_14 *)arg2)->unk_2C;
                    if (temp_v0_5 != 0) {
                        temp_a1 = *(temp_v0_5 + direction_index);
                        ASM_USE_NV(direction_index);   /* MATCH pin: load-bearing for the whole function shape */
                        func_80047738(arg2, temp_a1, ((S_8016B0E8_14 *)arg2)->unk_04);
                    }
                    ((S_8016B0E8_0 *)arg0)->unk_94 = temp_s0_2;
                }
                temp_v0_3 = D_8006CCF8[temp_s1];
                ASM_USE_NV(temp_s1);   /* MATCH pin: load-bearing for the whole function shape */
                if (temp_v0_3 != 0) {
                    tail_flag = ((S_8016B0E8_14 *)arg2)->unk_14.n | 1;
                    ASM_TAILSLOT_PIN(tail_flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    func_8016B518();
                    return;
                }
                ((S_8016B0E8_14 *)arg2)->unk_14.v = (u16) (((S_8016B0E8_14 *)arg2)->unk_14.v & 0xFFFE);
                if (!(((S_8016B0E8_2 *)obj)->unk_1C & 0x20)) {
                    if (((S_8016B0E8_14 *)arg2)->unk_14.v & 0x40) {
                        goto block_after_7000;
                    }
                    {
                        func_800478B8(arg2);
                        func_8016B564();
                        return;
                    }
                }
                ((S_8016B0E8_14 *)arg2)->unk_14.n = (u16) (((S_8016B0E8_14 *)arg2)->unk_14.n | 0x7000);
block_after_7000:
                func_800A020C(((S_8016B0E8_2 *)obj)->unk_1C, arg2 + 0xC);
                func_8016B588();
                return;
            }
            tail_predicate = temp_v1_6 & 0x800;
            if (tail_predicate) {
                var_v0_3 = temp_v1_6 & 0x8FFF;
            } else {
                var_v0_3 = temp_v1_6 | 0x7000;
            }
            ((S_8016B0E8_14 *)arg2)->unk_14.n = var_v0_3;
            ((S_8016B0E8_15 *)arg1)->unk_00.at00.v = (s32) (((S_8016B0E8_15 *)arg1)->unk_00.at00.v + ((S_8016B0E8_15 *)arg1)->unk_0C);
            ((S_8016B0E8_15 *)arg1)->unk_04.at00.v = (s32) (((S_8016B0E8_15 *)arg1)->unk_04.at00.v + ((S_8016B0E8_15 *)arg1)->unk_10);
            if (!(((S_8016B0E8_0 *)arg0)->unk_98 & 8)) {
                goto block_after_b5f4;
            }
block_tail_b5f4:
            ((S_8016B0E8_0 *)arg0)->unk_9D = 0;
            {
                func_8016B5F4();
                return;
            }
block_after_b5f4:
            ((S_8016B0E8_15 *)arg1)->unk_14 = (s32) (((S_8016B0E8_15 *)arg1)->unk_14 + (((S_8016B0E8_0 *)arg0)->unk_9D * 0x14000));
            temp_v0_3 = (u8) ((S_8016B0E8_0 *)arg0)->unk_9D + 1;
            ((S_8016B0E8_0 *)arg0)->unk_9D = (s8) temp_v0_3;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
            motion_position = ((S_8016B0E8_0 *)arg0)->unk_90.at00.v;
            motion_delta = ((S_8016B0E8_15 *)arg1)->unk_14;
            motion_flags = ((S_8016B0E8_0 *)arg0)->unk_98;
            motion_position += motion_delta;
            ((S_8016B0E8_0 *)arg0)->unk_90.at00.v = motion_position;
            if (!(motion_flags & 4)) {
                temp_v0_6 = func_800BCB04(((S_8016B0E8_15 *)arg1)->unk_00.at02.v, ((S_8016B0E8_15 *)arg1)->unk_04.at02.v, (s16) (((S_8016B0E8_2 *)obj)->unk_88.u - 0x20));
                if (temp_v0_6 < 0x200) {
                    temp_a2 = (s16) ((S_8016B0E8_2 *)obj)->unk_88.u;
                    temp_a0_4 = ((S_8016B0E8_2 *)obj)->unk_88.u;
                    if (!((((S_8016B0E8_0 *)arg0)->unk_90.at02.v + temp_a2) < temp_v0_6)) {
                        goto block_check_b68c;
                    }
block_tail_b6a4:
                    ((S_8016B0E8_2 *)obj)->unk_1C = (s32) (((S_8016B0E8_2 *)obj)->unk_1C & 0xF7FFFFFF);
                    {
                        func_8016B6A4();
                        return;
                    }
block_check_b68c:
                    if (temp_v0_6 < temp_a2) {
                        goto block_normal_motion;
                    }
block_tail_b68c:
                    ((S_8016B0E8_0 *)arg0)->unk_90.at00.v = 0;
                    {
                        func_8016B68C();
                        return;
                    }
block_normal_motion:
                    height_delta = temp_v0_6 - temp_a0_4;
                    ((S_8016B0E8_0 *)arg0)->unk_90.at02.v = height_delta;
                    ((S_8016B0E8_15 *)arg1)->unk_14 = 0;
                    ((S_8016B0E8_2 *)obj)->unk_1C = (s32) (((S_8016B0E8_2 *)obj)->unk_1C | 0x08000000);
                    ((S_8016B0E8_0 *)arg0)->unk_9D = 0;
                    temp_v1_7 = ((S_8016B0E8_2 *)obj)->unk_1C;
                    if (temp_v1_7 & 0x40000000) {
                        ((S_8016B0E8_2 *)obj)->unk_1C = (s32) (temp_v1_7 & 0xBFFFFFFF);
                        temp_v0_6 = func_800BCB04((((S_8016B0E8_14 *)arg2)->unk_24 << 6) | 0x20, (((S_8016B0E8_14 *)arg2)->unk_25 << 6) | 0x20, (s16) (((S_8016B0E8_2 *)obj)->unk_88.u - 0x20));
                        ((S_8016B0E8_0 *)arg0)->unk_90.at02.v = (s16) ((u16) ((S_8016B0E8_0 *)arg0)->unk_90.at02.v + (((S_8016B0E8_2 *)obj)->unk_88.u - temp_v0_6));
                        ((S_8016B0E8_2 *)obj)->unk_88.s = temp_v0_6;
                        func_8016B724();
                        return;
                    }
                    goto block_67;
                }
            }
            ((S_8016B0E8_2 *)obj)->unk_1C = (s32) (((S_8016B0E8_2 *)obj)->unk_1C & 0xF7FFFFFF);
block_67:
            ((S_8016B0E8_15 *)arg1)->unk_0A = (s16) (((S_8016B0E8_2 *)obj)->unk_88.u + (u16) ((S_8016B0E8_0 *)arg0)->unk_90.at02.v);
            ((S_8016B0E8_14 *)arg2)->unk_14.n = (u16) (((S_8016B0E8_14 *)arg2)->unk_14.n | 0x40);
        }
block_return:
    return;
}
