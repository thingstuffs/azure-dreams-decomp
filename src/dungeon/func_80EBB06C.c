#include "common.h"

typedef struct S_8016A86C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A86C_0;   /* obj in func_8016A86C */

typedef struct S_8016A86C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A86C_1;   /* work in func_8016A86C */

typedef struct S_8016A86C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A86C_2;   /* part_a in func_8016A86C */

typedef struct S_8016A86C_3 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_8016A86C_3;   /* part_b in func_8016A86C */

typedef struct S_8016A86C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
    u8 pad_A0[0x8];
    u16 unk_A8;
} S_8016A86C_4;   /* actor in func_8016A86C */

typedef struct S_8016A86C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A86C_5;   /* current in func_8016A86C */

typedef struct S_8016A86C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8016A86C_6;   /* child in func_8016A86C */

typedef struct S_8016A86C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    u32 unk_28;
} S_8016A86C_7;   /* elem in func_8016A86C */

typedef struct S_8016A86C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A86C_8;   /* base in func_8016A86C */

typedef struct S_8016A86C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8016A86C_9;   /* ((S_8016A86C_8 *)base)->unk_A4 in func_8016A86C */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_80047784();
extern void func_800478E8();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800D71A8[];
extern u8 D_800D78C0[];
extern u8 D_8016AB64[];
extern u8 D_8016B1A4[];
extern u8 D_8016E18C[];
extern u8 D_8016E1CC[];

void *func_8016A86C(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *work ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s8 saved_arg1 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s8 saved_arg2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *obj;
    S_8016A86C_2 *part_a;
    S_8016A86C_3 *part_b;
    S_8016A86C_4 *actor;
    s32 left;
    s32 right;
    s16 saved_arg0;
    void *current;
    S_8016A86C_8 *base;
    void *child_obj;
    S_8016A86C_7 *elem;
    s32 count;
    register s32 i;
    register s32 elem_offset ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    s32 child_arg;
    u16 flags;
    u16 child_flags;
    u16 elem_flags;
    register s32 call_code ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_zero ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 color ASM_REG("$8");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    work = 0;
    saved_arg2 = arg2;
    saved_arg0 = arg0;
    obj = func_8003FD64(0x112, (saved_arg1 = arg1, D_80083498));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A86C_0 *)obj)->unk_10 = D_8016AB64;
        ((S_8016A86C_1 *)work)->unk_13 = 0x21;
        func_8004491C(obj, &D_80045340);
        actor = work;

        part_a = ((S_8016A86C_0 *)obj)->unk_08;
        part_a->unk_0A = arg3;
        part_b = ((S_8016A86C_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_2C = D_8016E18C;
        part_b->unk_24 = saved_arg1;
        part_b->unk_25 = saved_arg2;

        if (kind == 1) {
            left = ((S_8016A86C_1 *)work)->unk_14 | 0x6000;
            right = ((S_8016A86C_1 *)work)->unk_1C | 0x6000;
            goto set_kind_flags;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = ((S_8016A86C_1 *)work)->unk_14 | 0x2000;
        right = ((S_8016A86C_1 *)work)->unk_1C | 0x2000;

set_kind_flags:
        ((S_8016A86C_1 *)work)->unk_14 = left;
        ((S_8016A86C_1 *)work)->unk_1C = right;
        goto call_actor_setup;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(((S_8016A86C_1 *)work)->unk_14 & 0x200)) {
                left = func_800A6D30();
                if (left & 1) {
                    ((S_8016A86C_1 *)work)->unk_1C |= 0x200;
                    right = func_800A6D30();
                    func_800A48F0(work, 1, (right & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016E1CC;
                }
            }
        }

call_actor_setup:
        func_800A9C18(obj, part_a, part_b, saved_arg0);

        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_8016B1A4;
        ((S_8016A86C_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -16;
        flags = actor->unk_98;
        actor->unk_A8 = 0;
        actor->unk_9E = 1;
        actor->unk_98 = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = func_8003FD64(0x112, D_80083498);
            ((S_8016A86C_5 *)current)->unk_A4 = child_obj;
            if (child_obj != 0) {
                register void *child ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

                child = (u8 *)child_obj + 0x20;

                ((S_8016A86C_6 *)child)->unk_02 = 1;
                i = 0;
                base = current;
                elem_offset = 8;
                while (i < ((S_8016A86C_6 *)child)->unk_02) {
                    color = 0x00C0C0C0;
                    elem = (u8 *)child + elem_offset;
                    ASM_KEEP(elem);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    call_code = 39;
                    child_flags = ((S_8016A86C_6 *)child)->unk_04;
                    ASM_KEEP(child_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    call_zero = 0;
                    ASM_KEEP_NV(call_zero);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    ((S_8016A86C_6 *)child)->unk_04 = child_flags | 0x8000;
                    child_arg = part_b->unk_28;
                    elem_flags = elem->unk_14;
                    elem->unk_10 = 96;
                    elem->unk_28 = child_arg;
                    elem->unk_14 = elem_flags | 0xC;
                    elem_offset += 48;
                    elem->unk_12 = part_b->unk_12 - 128;
                    elem->unk_0C = color;
                    ((S_8016A86C_9 *)(base->unk_A4))->unk_10 = D_800D78C0;
                    i++;
                    func_80047784(elem, call_code, call_zero, child_arg);
                    ((S_8016A86C_6 *)child)->unk_06 = 0;
                    func_800478E8(part_b, D_800D71A8, 0);
                    ((S_8016A86C_6 *)child)->unk_98 = (u8 *)obj + 30;
                }
            }
            current = (u8 *)current + 4;
            count++;
        } while (count < actor->unk_9E);
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
