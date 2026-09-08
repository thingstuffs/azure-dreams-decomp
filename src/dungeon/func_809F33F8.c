/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

/* Value-preserving cse-equivalence launder for the first callback's 4th
 * argument: a block-scoped $a0-pinned temp with the empty "=r"/"0" tie
 * (expression form of ASM_REG+ASM_KEEP_NV). Port build folds to the plain
 * value. */
#ifdef NON_MATCHING
#define KEEP_A0_EXPR(v) (v)
#else
#define KEEP_A0_EXPR(v) ({ register void *t_ ASM_REG("$4") = (v); ASM_KEEP_NV(t_); t_; })
#endif

void func_80047738(void *, u8, s8);              /* extern */
void func_80047784(void *, u8, s32);             /* extern */
void func_800478B8(void *);                       /* extern */
s32 func_800644B8(s32);                            /* extern */
M2C_UNK func_800A020C(s32, void *);               /* extern */
s32 func_800A9E70(void *, void *, void *, void *); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(s32, s32, s16);                 /* extern */
void func_80170D94(void) __attribute__((noreturn));  /* extern */
void func_80170E3C(void) __attribute__((noreturn));  /* extern */
void func_80170EB8(void) __attribute__((noreturn));  /* extern */
void func_80170F54(void) __attribute__((noreturn));  /* extern */
void func_80171210(void) __attribute__((noreturn));  /* extern */
void func_80171320(void) __attribute__((noreturn));  /* extern */
void func_80171330(void) __attribute__((noreturn));  /* extern */
extern u8 D_8006CCF8[12];
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern M2C_UNK D_80171400[3];
extern u8 D_80175140[12];
extern u8 D_80175148[12];
extern u8 D_80175170[12];
extern u8 D_80175178[12];
extern void *D_80175198[3];


typedef struct S_80170BF8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x1A];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u8 pad_9E[0xA];
    s16 unk_A8;
} S_80170BF8_0;   /* arg0 in func_80170BF8 */

typedef struct S_80170BF8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170BF8_1;   /* arg1 in func_80170BF8 */

typedef struct S_80170BF8_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170BF8_2;   /* arg2 in func_80170BF8 */

typedef struct S_80170BF8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170BF8_3;   /* actor2 in func_80170BF8 */

void func_80170BF8(void *arg0_, void *arg1_, void *arg2_) {
    u16 initial_flags = D_80083462[0];
    register void *actor ASM_REG("$17") = arg0_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *motion ASM_REG("$21") = arg1_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *object ASM_REG("$20") = arg2_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s6 = 0;
    void *actor2 = actor;
#define arg0 actor
#define arg1 motion
#define arg2 object

    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    u8 *temp_v1_5;
    u8 *temp_v1_8;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 *var_v0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 var_v0_3;
    s32 temp_a0;
    s16 temp_a1;
    s32 temp_v1_10;
    s32 temp_v1_3;
    s32 temp_v1_6;
    s32 temp_final;
    u32 address_1;
    u32 page_base;
    register u32 tail_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u32 temp_dead;
    u16 temp_v0_3;
    u16 temp_v1_2;
    u16 temp_v1_4;
    u16 temp_v1_7;
    u16 temp_v1_9;
    u16 var_v0_2;
    s32 temp_s3;
    s16 temp_s0;
    if (initial_flags & 0x2000) {
            temp_v1 = ((S_80170BF8_0 *)arg0)->unk_8C;
        if (temp_v1 == &D_80171400) {
            temp_v1(arg0_, arg1_, arg2_, KEEP_A0_EXPR(arg0_));
            return;
        }
        ((S_80170BF8_0 *)arg0)->unk_71 = (u8) (((S_80170BF8_0 *)arg0)->unk_71 & 0x7F);
        return;
    }
    ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(motion);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(object);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_s0 = (s8) ((S_80170BF8_0 *)arg0)->unk_6D;
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = ((S_80170BF8_0 *)arg0)->unk_8C;
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        ((void (*)(void *, void *, void *, void *))D_80175198[((S_80170BF8_0 *)arg0)->unk_9A])(arg0, arg1, arg2, arg0);
        if ((s16) temp_s0 != (s8) ((S_80170BF8_0 *)arg0)->unk_6D) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        ((S_80170BF8_1 *)arg1)->unk_00.at00.v = (s32) (((S_80170BF8_1 *)arg1)->unk_00.at00.v + ((S_80170BF8_1 *)arg1)->unk_0C);
        ((S_80170BF8_1 *)arg1)->unk_04.at00.v = (s32) (((S_80170BF8_1 *)arg1)->unk_04.at00.v + ((S_80170BF8_1 *)arg1)->unk_10);
        if (!(((S_80170BF8_0 *)arg0)->unk_1C & 0x40000) && !(((S_80170BF8_0 *)arg0)->unk_98 & 8)) {
            ((S_80170BF8_1 *)arg1)->unk_14 = (s32) (((S_80170BF8_1 *)arg1)->unk_14 + (((S_80170BF8_0 *)arg0)->unk_9D.s * 0x14000));
            ((S_80170BF8_0 *)arg0)->unk_9D.u = (u8) (((S_80170BF8_0 *)arg0)->unk_9D.u + 1);
            func_80170D94();
            return;
        }
        ((S_80170BF8_0 *)arg0)->unk_9D.s = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_80170BF8_0 *)arg0)->unk_90.at00.v = (s32) (((S_80170BF8_0 *)arg0)->unk_90.at00.v + ((S_80170BF8_1 *)arg1)->unk_14);
        temp_v1_2 = ((S_80170BF8_2 *)arg2)->unk_14;
        if (!(temp_v1_2 & 0x8000)) {
            temp_s3 = ((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor2)->unk_2A + 0x100) >> 9) & 7;
            temp_s0 = (s16) temp_s3;
            if (((S_80170BF8_0 *)arg0)->unk_94 != temp_s0) {
                func_80047738(arg2, *(((S_80170BF8_2 *)arg2)->unk_2C + temp_s0), ((S_80170BF8_2 *)arg2)->unk_04);
                ((S_80170BF8_0 *)arg0)->unk_94 = temp_s3;
            }
            if (D_8006CCF8[temp_s0] != 0) {
                temp_dead = ((S_80170BF8_2 *)arg2)->unk_14;
                temp_dead |= 1;
                ASM_TAILSLOT_PIN(temp_dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80170E3C();
                return;
            }
            ((S_80170BF8_2 *)arg2)->unk_14 = (u16) (((S_80170BF8_2 *)arg2)->unk_14 & 0xFFFE);
            if (((S_80170BF8_0 *)arg0)->unk_9A != 8) {
                func_800A020C(((S_80170BF8_3 *)actor2)->unk_1C, arg2 + 0xC);
            }
            if (!(((S_80170BF8_3 *)actor2)->unk_1C & 0x20)) {
                if (!(((S_80170BF8_2 *)arg2)->unk_14 & 0x40)) {
                    func_800478B8(arg2);
                    page_base = 0xF7FF0000;
                    ASM_PAGEBASE_PIN(page_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_80170EB8();
                    return;
                }
                goto block_28;
            }
            ((S_80170BF8_2 *)arg2)->unk_14 = (u16) (((S_80170BF8_2 *)arg2)->unk_14 | 0x7000);
            ((S_80170BF8_3 *)actor2)->unk_1C = (s32) (((S_80170BF8_3 *)actor2)->unk_1C & 0xFFFBFFFF);
block_28:
            temp_v1_3 = ((S_80170BF8_3 *)actor2)->unk_1C & 0xF7FFFFFF;
            ((S_80170BF8_3 *)actor2)->unk_1C = temp_v1_3;
            if (temp_v1_3 & 0x40000) {
                if (!(((S_80170BF8_2 *)arg2)->unk_14 & 0x40)) {
                    temp_v1_4 = ((S_80170BF8_0 *)arg0)->unk_98;
                    if (temp_v1_4 & 0x8000) {
                        ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (temp_v1_4 & 0x7FFF);
            temp_v1_5 = ((S_80170BF8_2 *)arg2)->unk_2C;
                        var_a1 = D_80175148;
                        if (temp_v1_5 == D_80175148) {
                            tail_value = (u32) D_80175140;
                            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            func_80170F54();
                            return;
                        }
                        if (temp_v1_5 != D_80175140) {
                            var_a1 = D_80175170;
                            if (temp_v1_5 == D_80175170) {
                                tail_value = (u32) D_80175178;
                                ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                                func_80170F54();
                                return;
                            }
                            if (temp_v1_5 == D_80175178) {
                                goto block_39;
                            }
                            goto block_40;
                        }
block_39:
                        ((S_80170BF8_2 *)arg2)->unk_2C = var_a1;
                        address_1 = (u32) ((((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor2)->unk_2A + 0x100) >> 9) & 7));
                        address_1 += (u32) var_a1;
                        func_80047784(arg2, *(u8 *) address_1, 0);
                        goto block_40;
                    }
block_40:
                        if (((S_80170BF8_2 *)arg2)->unk_14 & 0x6000) {
                        ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (((S_80170BF8_0 *)arg0)->unk_98 | 0x8000);
                        if (((S_80170BF8_2 *)arg2)->unk_2C == D_80175140) {
                            ((S_80170BF8_0 *)arg0)->unk_A8 = 0;
                        }
                    }
                    var_s6 = func_800644B8((((S_80170BF8_0 *)arg0)->unk_A8 << 0xC) / 20) >> 0xA;
                    ((S_80170BF8_0 *)arg0)->unk_A8 = (s16) ((u16) ((S_80170BF8_0 *)arg0)->unk_A8 + 1);
                    goto block_44;
                }
block_44:
                if (!(((S_80170BF8_0 *)arg0)->unk_98 & 8)) {
                    temp_v0_2 = (s16) (func_800BCB04(((S_80170BF8_1 *)arg1)->unk_00.at02.v, ((S_80170BF8_1 *)arg1)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor2)->unk_88.u - 0x20)) - ((S_80170BF8_3 *)actor2)->unk_88.u);
                    temp_v1_9 = (u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v;
                    if (((S_80170BF8_0 *)arg0)->unk_90.at02.v > (temp_v0_2 - 0x20)) {
                        ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) (temp_v1_9 - 8);
                        func_80171330();
                        return;
                    }
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    if (((S_80170BF8_0 *)arg0)->unk_90.at02.v < (temp_v0_2 - 0x2A)) {
                        ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) (temp_v1_9 + 8);
                        func_80171330();
                        return;
                    }
                    goto block_82;
                }
                goto block_82;
            }
            temp_v0_3 = ((S_80170BF8_0 *)arg0)->unk_98;
            ((S_80170BF8_0 *)arg0)->unk_A8 = 0;
            ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (temp_v0_3 & 0x7FFF);
            if (!(temp_v0_3 & 8)) {
                temp_a0 = func_800BCB04(((S_80170BF8_1 *)arg1)->unk_00.at02.v, ((S_80170BF8_1 *)arg1)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor2)->unk_88.u - 0x20));
                temp_v0_4 = (s16) temp_a0;
                temp_a0_3 = ((S_80170BF8_3 *)actor2)->unk_88.s;
                temp_a0 = (s32) temp_v0_4 - temp_a0_3;
                if (temp_a0 < ((S_80170BF8_0 *)arg0)->unk_90.at02.v) {
                    ((S_80170BF8_0 *)arg0)->unk_90.at02.v = temp_a0;
                    ((S_80170BF8_0 *)arg0)->unk_9D.s = 0;
                    ((S_80170BF8_1 *)arg1)->unk_14 = 0;
                    ((S_80170BF8_3 *)actor2)->unk_1C = ((S_80170BF8_3 *)actor2)->unk_1C | 0x08000000;
                    func_80171330();
                    return;
                }
            }
            goto block_82;
        }
        ((S_80170BF8_2 *)arg2)->unk_14 = (temp_v1_2 & 0x800) ? (temp_v1_2 & 0x8FFF) : (temp_v1_2 | 0x7000);
        temp_v1_6 = ((S_80170BF8_3 *)actor2)->unk_1C & 0xF7FFFFFF;
        ((S_80170BF8_3 *)actor2)->unk_1C = temp_v1_6;
        if (!(temp_v1_6 & 0x40000)) {
            ((S_80170BF8_0 *)arg0)->unk_A8 = 0;
            ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) ((u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v - var_s6);
            var_s6 = 0;
            if (!(((S_80170BF8_0 *)arg0)->unk_98 & 8)) {
                temp_a0 = func_800BCB04(((S_80170BF8_1 *)arg1)->unk_00.at02.v, ((S_80170BF8_1 *)arg1)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor2)->unk_88.u - 0x20));
                temp_v0_5 = (s16) temp_a0;
                temp_a0_4 = ((S_80170BF8_3 *)actor2)->unk_88.s;
                temp_a0 = (s32) temp_v0_5 - temp_a0_4;
                if (temp_a0 < ((S_80170BF8_0 *)arg0)->unk_90.at02.v) {
                    ((S_80170BF8_0 *)arg0)->unk_90.at02.v = temp_a0;
                    ((S_80170BF8_0 *)arg0)->unk_9D.s = 0;
                    ((S_80170BF8_1 *)arg1)->unk_14 = 0;
                    ((S_80170BF8_3 *)actor2)->unk_1C = ((S_80170BF8_3 *)actor2)->unk_1C | 0x08000000;
                    func_80171320();
                    return;
                }
            }
            goto block_81;
        }
        if (!(((S_80170BF8_2 *)arg2)->unk_14 & 0x40)) {
            temp_v1_7 = ((S_80170BF8_0 *)arg0)->unk_98;
            if (temp_v1_7 & 0x8000) {
                ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (temp_v1_7 & 0x7FFF);
                        temp_v1_8 = ((S_80170BF8_2 *)arg2)->unk_2C;
                var_a1_2 = D_80175148;
                if (temp_v1_8 == D_80175148) {
                    tail_value = (u32) D_80175140;
                    ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    func_80171210();
                    return;
                }
                if (temp_v1_8 != D_80175140) {
                    var_a1_2 = D_80175170;
                    if (temp_v1_8 == D_80175170) {
                        tail_value = (u32) D_80175178;
                        ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        func_80171210();
                        return;
                    }
                    if (temp_v1_8 == D_80175178) {
                        goto block_72;
                    }
                    goto block_73;
                }
block_72:
                ((S_80170BF8_2 *)arg2)->unk_2C = var_a1_2;
                address_1 = (u32) ((((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor2)->unk_2A + 0x100) >> 9) & 7));
                address_1 += (u32) var_a1_2;
                func_80047784(arg2, *(u8 *) address_1, 0);
                goto block_73;
            }
block_73:
            if (((S_80170BF8_2 *)arg2)->unk_14 & 0x6000) {
                ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (((S_80170BF8_0 *)arg0)->unk_98 | 0x8000);
                if (((S_80170BF8_2 *)arg2)->unk_2C == D_80175140) {
                    ((S_80170BF8_0 *)arg0)->unk_A8 = 0;
                }
            }
            var_s6 = func_800644B8((((S_80170BF8_0 *)arg0)->unk_A8 << 0xC) / 20) >> 0xA;
            ((S_80170BF8_0 *)arg0)->unk_A8 = (s16) ((u16) ((S_80170BF8_0 *)arg0)->unk_A8 + 1);
            goto block_77;
        }
block_77:
        if (!(((S_80170BF8_0 *)arg0)->unk_98 & 8)) {
            temp_v0_6 = func_800BCB04(((S_80170BF8_1 *)arg1)->unk_00.at02.v, ((S_80170BF8_1 *)arg1)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor2)->unk_88.u - 0x20)) - ((S_80170BF8_3 *)actor2)->unk_88.u;
            temp_a0_5 = ((S_80170BF8_0 *)arg0)->unk_90.at02.v;
            if (temp_a0_5 > (temp_v0_6 - 0x20)) {
                temp_v1_9 = (u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v;
                ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) (temp_v1_9 - 8);
            } else if (temp_a0_5 < (temp_v0_6 - 0x2A)) {
                temp_v1_9 = (u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v;
                ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) (temp_v1_9 + 8);
            }
        }
block_81:
        ((S_80170BF8_0 *)arg0)->unk_A8 = 0;
        ((S_80170BF8_0 *)arg0)->unk_98 = (u16) (((S_80170BF8_0 *)arg0)->unk_98 & 0x7FFF);
block_82:
        temp_v1_10 = ((S_80170BF8_3 *)actor2)->unk_1C;
        if (temp_v1_10 & 0x40000000) {
            ((S_80170BF8_3 *)actor2)->unk_1C = (s32) (temp_v1_10 & 0xBFFFFFFF);
            temp_v0_7 = func_800BCB04((((S_80170BF8_2 *)arg2)->unk_24 << 6) | 0x20, (((S_80170BF8_2 *)arg2)->unk_25 << 6) | 0x20, (s16) (((S_80170BF8_3 *)actor2)->unk_88.u - 0x20));
            if (temp_v0_7 < 0x200) {
                ((S_80170BF8_0 *)arg0)->unk_90.at02.v = (s16) ((u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v + (((S_80170BF8_3 *)actor2)->unk_88.u - temp_v0_7));
                ((S_80170BF8_3 *)actor2)->unk_88.u = (u16) temp_v0_7;
            }
        }
        temp_final = (s32) (((S_80170BF8_3 *)actor2)->unk_88.u + (u16) ((S_80170BF8_0 *)arg0)->unk_90.at02.v + var_s6);
        ((S_80170BF8_1 *)arg1)->unk_0A = (s16) temp_final;
        ((S_80170BF8_2 *)arg2)->unk_14 = (u16) (((S_80170BF8_2 *)arg2)->unk_14 | 0x40);
    }
}
