#include "common.h"


typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern u8 D_8006CCF8[];
extern u16 D_80083462;
extern s16 D_80083228;
extern u8 D_80170E54;
extern EntityCallback D_80173CEC[];


typedef struct S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170A28_0;   /* arg2 in func_80170A28 */

typedef struct S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_80170A28_1;   /* entity in func_80170A28 */

typedef struct S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A28_2;   /* arg1 in func_80170A28 */

void func_80170A28(void *input0, void *input1, void *input2)
{
    register void *arg0 ASM_REG("$18") = input0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80170A28_2 *arg1 = input1;
    void *arg2 = input2;
    register void *entity ASM_REG("$17") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 work;
    register s32 direction_copy ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *call0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call3;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 state_load ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 tail_value;
    register s32 floor_height ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    EntityCallback callback;
    s32 arithmetic;
    s16 height;
    s16 base_height;
    s32 previous_direction;
    s32 flags;
    s32 compare_new;
    u16 part_flags;
    u16 new_part_flags;
    u8 table_value;

    if (D_80083462 & 0x2000) {
        callback = (*(EntityCallback *)((u8 *)arg0 + 0x8C));
        if (callback == (EntityCallback)&D_80170E54) {
            {
                void *self;
                self = input0;
                ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                callback(self, input1, input2, self);
            }
            goto done;
        }
        (*(u8 *)((u8 *)arg0 + 0x71)) &= 0x7F;
        goto done;
    }

    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    call0 = arg0;
    call1 = arg1;
    call2 = arg2;
    state_load = (*(u8 *)((u8 *)arg0 + 0x6D));
    call3 = arg0;
    work = (s8)state_load;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
        return;
    }

    {
        EntityCallback callback2;
        callback2 = (*(EntityCallback *)((u8 *)arg0 + 0x8C));
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, arg0);
        }
    }
    D_80173CEC[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0);

    state_load = (s32)work << 16;
    compare_new = (*(s8 *)((u8 *)arg0 + 0x6D));
    state_load >>= 16;
    if (state_load != compare_new) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    part_flags = ((S_80170A28_0 *)arg2)->unk_14.n;
    if (!(part_flags & 0x8000)) {
        arithmetic = D_80083228 + (*(s16 *)((u8 *)arg0 + 0x2A)) + 0x100;
        work = (arithmetic >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)arg0 + 0x94));
        direction_copy = (u16)work;
        if (previous_direction != work) {
            if (((S_80170A28_0 *)arg2)->unk_2C != 0) {
                func_80047738(arg2,
                              ((S_80170A28_0 *)arg2)->unk_2C[work],
                              ((S_80170A28_0 *)arg2)->unk_04);
            }
            (*(s16 *)((u8 *)arg0 + 0x94)) = work;
        }

        table_value = D_8006CCF8[direction_copy];
        ASM_KEEP(direction_copy);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (table_value != 0) {
            ((S_80170A28_0 *)arg2)->unk_14.n |= 1;
        } else {
            ((S_80170A28_0 *)arg2)->unk_14.n &= 0xFFFE;
        }
        if (!(((S_80170A28_1 *)entity)->unk_1C & 0x20)) {
            if (!(((S_80170A28_0 *)arg2)->unk_14.v & 0x40)) {
                func_800478B8(arg2);
                goto after_part_flags;
            }
        } else {
            ((S_80170A28_0 *)arg2)->unk_14.v |= 0x7000;
        }
after_part_flags:
        func_800A020C(((S_80170A28_1 *)entity)->unk_1C, (u8 *)arg2 + 0xC);
        goto motion;
    }

    if (part_flags & 0x800) {
        new_part_flags = part_flags & 0x8FFF;
    } else {
        new_part_flags = part_flags | 0x7000;
    }
    ((S_80170A28_0 *)arg2)->unk_14.n = new_part_flags;

motion:
    arg1->unk_00.at00.v += arg1->unk_0C;
    arg1->unk_04.at00.v += arg1->unk_10;

    if ((*(u16 *)((u8 *)arg0 + 0x98)) & 8) {
        (*(s8 *)((u8 *)arg0 + 0x9D)) = 0;
        goto accumulate;
    }

    arg1->unk_14 += (*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000;
    (*(s8 *)((u8 *)arg0 + 0x9D)) = (u8)(*(s8 *)((u8 *)arg0 + 0x9D)) + 1;
accumulate:
    (*(s32 *)((u8 *)arg0 + 0x90)) += arg1->unk_14;

    if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 4)) {
        height = func_800BCB04(arg1->unk_00.at02.v,
                               arg1->unk_04.at02.v,
                               (s16)(((S_80170A28_1 *)entity)->unk_88 - 0x20));
        if (height < 0x200) {
            base_height = (s16)((S_80170A28_1 *)entity)->unk_88;
            if ((*(s16 *)((u8 *)arg0 + 0x92)) + base_height < height) {
                ((S_80170A28_1 *)entity)->unk_1C &= 0xF7FFFFFF;
                goto flags_test;
            }
            if (height >= base_height) {
                (*(s32 *)((u8 *)arg0 + 0x90)) = 0;
                arg1->unk_14 = 0;
                ((S_80170A28_1 *)entity)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)arg0 + 0x9D)) = 0;
                goto flags_test;
            }

            arg1->unk_14 = 0;
            ((S_80170A28_1 *)entity)->unk_1C |= 0x08000000;
            (*(s8 *)((u8 *)arg0 + 0x9D)) = 0;
            (*(s16 *)((u8 *)arg0 + 0x92)) = height - ((S_80170A28_1 *)entity)->unk_88;

flags_test:
            flags = ((S_80170A28_1 *)entity)->unk_1C;
            if (flags & 0x40000000) {
                ((S_80170A28_1 *)entity)->unk_1C = flags & 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (((S_80170A28_0 *)arg2)->unk_24 << 6) | 0x20,
                    (((S_80170A28_0 *)arg2)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170A28_1 *)entity)->unk_88 - 0x20));
                (*(s16 *)((u8 *)arg0 + 0x92)) +=
                    ((S_80170A28_1 *)entity)->unk_88 - floor_height;
                ((S_80170A28_1 *)entity)->unk_88 = floor_height;
                goto finish;
            }
            goto finish;
        }
    }

    ((S_80170A28_1 *)entity)->unk_1C &= 0xF7FFFFFF;

finish:
    arg1->unk_0A =
        ((S_80170A28_1 *)entity)->unk_88 + (*(u16 *)((u8 *)arg0 + 0x92));
    ((S_80170A28_0 *)arg2)->unk_14.n |= 0x40;

done:
    return;
}
