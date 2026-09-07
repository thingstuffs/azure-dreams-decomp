#include "common.h"

extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064CF0(void *arg0);
extern void func_80064D80(void *arg0);
extern void func_80065450(void *arg0, void *arg1, s32 *arg2);
extern void func_80065820(void *arg0, void *arg1);
extern void func_80065AB0(s16 arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80065C50(s16 arg0, void *arg1);
extern void func_80065DF0(s16 arg0, void *arg1);

typedef struct {
    /* 0x00 */ s32 *unk00;
    /* 0x04 */ s16 *unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u16 unk1A;
} Struct_800D6330;

void func_800DBA90(Struct_800D6330 *arg0) {
    /* One combined stack buffer for sp10 (zero-loop scratch), sp24/28/2c
       (dead-store idiom: computed but never re-read; kept live purely by
       address-escape of the LATER part of this same buffer), and sp30/34/38
       (out params of func_80065450) + sp40. Splitting these into separate
       locally-scoped arrays makes each individually address-taken buffer
       round up to its own 8-byte boundary and overshoots the real frame;
       one buffer matches the retail frame size exactly. */
    union {
        s16 sp10[9];
        struct {
            s8 pad1[0x14];
            s32 sp24;
            s32 sp28;
            s32 sp2C;
            s32 sp30;
            s32 sp34;
            s32 sp38;
        } s;
    } u;
    s32 sp40;
    s16 *ptr;
    s16 *row;
    s16 *cell;
    s32 outer;
    s32 two;
    s32 value;
    s32 offset;
    s32 *source;
    register void *output ASM_REG("$5");

    func_800649A0();
    u.s.sp24 = arg0->unk10;
    u.s.sp28 = arg0->unk12;
    u.s.sp2C = arg0->unk14;
    func_80064D80(u.sp10);
    if (arg0->unk1A == 0) {
        func_80065820((s8 *) arg0 + 8, u.sp10);
        goto post_init;
    }
    outer = 2;
    if (arg0->unk1A != 0x8000) {
        two = outer;
        value = 0x1000;
        ptr = u.sp10 + 6;
        do {
            sp40 = two;
            row = ptr;
            do {
                cell = (s16 *) ((sp40 << 1) + (u32) row);
                if (outer == sp40) {
                    *cell = value;
                } else {
                    *cell = 0;
                }
                sp40--;
            } while (sp40 >= 0);
            outer--;
            ptr -= 3;
        } while (outer >= 0);
        if (arg0->unk1A == 1) {
            func_80065AB0(arg0->unk08, u.sp10, value, two);
            func_80065C50(arg0->unk0A, u.sp10);
            func_80065DF0(arg0->unk0C, u.sp10);
        }
    }
post_init:
    func_80064CF0(u.sp10);
    outer = 0;
    if (arg0->unk18 > 0) {
        do {
            output = &u.s.sp30;
            ASM_KEEP(output);
            offset = outer * 8;
            source = arg0->unk00;
            ASM_SCHED_BARRIER();
            func_80065450((s8 *) source + offset, output, &sp40);
            *(u16 *) ((s8 *) arg0->unk04 + outer * 8) = *(u16 *) &u.s.sp30;
            *(u16 *) ((s8 *) arg0->unk04 + outer * 8 + 2) = *(u16 *) &u.s.sp34;
            *(u16 *) ((s8 *) arg0->unk04 + outer * 8 + 4) = *(u16 *) &u.s.sp38;
            outer++;
        } while (outer < arg0->unk18);
    }
    func_80064A40();
}

/* MECHANISM: True-space local joins and one stack aggregate produce the retail
   0x58 frame with s2/s1/s0 holds. The matrix loop reuses address-escaped sp40;
   integer-scaled cell addressing fixes its addu order. A guarded a1 call-arg
   pin plus one schedule seam closes the final sll/lw/a2 setup rotation. */
