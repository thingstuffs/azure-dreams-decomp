#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

extern void func_8015EF3C(void) __attribute__((noreturn));
extern void func_8015EFE4(void) __attribute__((noreturn));
extern void func_8015F050(void) __attribute__((noreturn));
extern void func_8015F408(void) __attribute__((noreturn));

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern void D_8015F4D4(void);
extern u8 D_801620E0[];
extern u8 D_801620E8[];
extern Callback D_80162168[];


typedef struct S_8015EDA8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8015EDA8_0;   /* arg1 in func_8015EDA8 */

typedef struct S_8015EDA8_1 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8015EDA8_1;   /* arg2 in func_8015EDA8 */

typedef struct S_8015EDA8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8015EDA8_2;   /* state in func_8015EDA8 */

void func_8015EDA8(void *arg0_, void *arg1_, void *arg2_)
{
    register void *arg0 ASM_REG("$17") = arg0_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *arg1 = arg1_;
    register void *arg2 ASM_REG("$20") = arg2_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *state ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    u8 *tail_value;
    s32 tail_index;
    s32 tail_state;
    void *tail_arg;
    register u8 *tail_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 old_state;
    s16 direction;
    s16 direction_copy;
    s32 height;
    s32 angle;
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 raw_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 ground;
    s16 delta;
    u16 part_flags;
    register u16 count ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 flags;
    s32 saved_offset;
    Callback callback;
    Callback callback2;

    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)arg0 + 0x8C));
        if (callback == (Callback)D_8015F4D4) {
            ASM_KEEP(arg0_);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            callback(arg0_, arg1_, arg2_, arg0_);
            return;
        }
        (*(u8 *)((u8 *)arg0 + 0x71)) &= 0x7F;
        return;
    }

    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    old_state = (s8)(*(u8 *)((u8 *)arg0 + 0x6D));
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    callback2 = (*(Callback *)((u8 *)arg0 + 0x8C));
    if (callback2 != 0) {
        callback2(arg0, arg1, arg2, arg0);
    }
    D_80162168[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0);
    if ((s16)old_state != (*(s8 *)((u8 *)arg0 + 0x6D))) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    ((S_8015EDA8_0 *)arg1)->unk_00.at00.v += ((S_8015EDA8_0 *)arg1)->unk_0C;
    ((S_8015EDA8_0 *)arg1)->unk_04.at00.v += ((S_8015EDA8_0 *)arg1)->unk_10;

    if (!((*(u32 *)((u8 *)arg0 + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
        ((S_8015EDA8_0 *)arg1)->unk_14 += (*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)arg0 + 0x9D))++;
        func_8015EF3C();
    }

    (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    (*(s32 *)((u8 *)arg0 + 0x90)) += ((S_8015EDA8_0 *)arg1)->unk_14;
    part_flags = ((S_8015EDA8_1 *)arg2)->unk_14;

    if (!(part_flags & 0x8000)) {
        direction = ((D_80083228 + ((S_8015EDA8_2 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_copy = direction;
        if ((*(s16 *)((u8 *)arg0 + 0x94)) != direction_copy) {
            func_80047738(arg2,
                (*(u8 *)((u8 *)(((S_8015EDA8_1 *)arg2)->unk_2C) + direction_copy)),
                ((S_8015EDA8_1 *)arg2)->unk_04.s8);
            (*(s16 *)((u8 *)arg0 + 0x94)) = direction;
        }
        if (D_8006CCF8[direction_copy] != 0) {
            u32 scratch;
            scratch = ((S_8015EDA8_1 *)arg2)->unk_14 | 1;
            ASM_TAILSLOT_PIN(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8015EFE4();
        }
        ((S_8015EDA8_1 *)arg2)->unk_14 &= 0xFFFE;
        func_800A020C(((S_8015EDA8_2 *)state)->unk_1C.s, (u8 *)arg2 + 0xC);
        if (!(((S_8015EDA8_2 *)state)->unk_1C.u & 0x20)) {
            if (!(((S_8015EDA8_1 *)arg2)->unk_14 & 0x40)) {
                func_800478B8(arg2);
                tail_value = (u8 *)0xF7FF0000;
                ASM_PAGEBASE_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_8015F050();
            }
        } else {
            ((S_8015EDA8_1 *)arg2)->unk_14 |= 0x7000;
            ((S_8015EDA8_2 *)state)->unk_1C.u &= 0xFFFBFFFF;
        }

        {
            u32 masked_flags;
            masked_flags = ((S_8015EDA8_2 *)state)->unk_1C.u & 0xF7FFFFFF;
            ((S_8015EDA8_2 *)state)->unk_1C.u = masked_flags;
            masked_flags &= 0x40000;
            if (!masked_flags) {
                goto reset_offset;
            }
        }

        if (!(((S_8015EDA8_1 *)arg2)->unk_14 & 0x40)) {
            if (((S_8015EDA8_1 *)arg2)->unk_2C == D_801620E0) {
                if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x100) {
                    (*(u16 *)((u8 *)arg0 + 0x9E)) = 0;
                }
                count = (*(u16 *)((u8 *)arg0 + 0x9E));
                angle = (s32)((u32)count << 16) >> 16;
                call_arg = angle * 0xE3;
                count++;
                (*(u16 *)((u8 *)arg0 + 0x9E)) = count;
                (*(s32 *)((u8 *)arg0 + 0xA0)) = func_800644B8(call_arg) << 7;
                if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x103) {
                    tail_base = D_801620E8;
                    (*(u8 * *)((u8 *)arg2 + 0x2C)) = tail_base;
                    tail_index = D_80083228;
                    tail_state = ((S_8015EDA8_2 *)state)->unk_2A;
                    tail_arg = arg2;
                    tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                    tail_value = &tail_base[tail_index];
                    goto play_tail_value_1;
                }
            } else if (((S_8015EDA8_1 *)arg2)->unk_2C == D_801620E8) {
                count = (*(u16 *)((u8 *)arg0 + 0x9E));
                angle = (s32)((u32)count << 16) >> 16;
                call_arg = angle * 0xE3;
                count++;
                (*(u16 *)((u8 *)arg0 + 0x9E)) = count;
                (*(s32 *)((u8 *)arg0 + 0xA0)) = func_800644B8(call_arg) << 7;
                if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x103) {
                    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801620E0;
                    tail_index = D_80083228;
                    tail_state = ((S_8015EDA8_2 *)state)->unk_2A;
                    tail_arg = arg2;
                    tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                    tail_value = &D_801620E0[tail_index];
play_tail_value_1:
                    func_80047784(tail_arg, *tail_value, 0);
                }
            }
        }

        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            s32 height_work = -0x20;
            height = (*(s16 *)((u8 *)arg0 + 0x92));
            raw_height = (*(u16 *)((u8 *)arg0 + 0x92));
            if (height_work < height) {
                height_work = raw_height - 8;
                (*(s16 *)((u8 *)arg0 + 0x92)) = height_work;
                func_8015F408();
            }
            goto low_height_adjustment;
        }
        goto final_adjustment;
    }

    ((S_8015EDA8_1 *)arg2)->unk_14 = (part_flags & 0x800)
        ? (part_flags & 0x8FFF)
        : (part_flags | 0x7000);
    ((S_8015EDA8_2 *)state)->unk_1C.u &= 0xF7FFFFFF;
    if (!(((S_8015EDA8_2 *)state)->unk_1C.u & 0x40000)) {
reset_offset:
        saved_offset = (*(s32 *)((u8 *)arg0 + 0xA0));
        (*(u16 *)((u8 *)arg0 + 0x9E)) = 0;
        (*(s32 *)((u8 *)arg0 + 0xA0)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x90)) -= saved_offset;
        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            ground = func_800BCB04(((S_8015EDA8_0 *)arg1)->unk_00.at02.v,
                ((S_8015EDA8_0 *)arg1)->unk_04.at02.v,
                (s16)(((S_8015EDA8_2 *)state)->unk_88 - 0x20));
            delta = ground - ((S_8015EDA8_2 *)state)->unk_88;
            if (delta < (*(s16 *)((u8 *)arg0 + 0x92))) {
                (*(s16 *)((u8 *)arg0 + 0x92)) = delta;
                (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
                ((S_8015EDA8_0 *)arg1)->unk_14 = 0;
                ((S_8015EDA8_2 *)state)->unk_1C.u |= 0x08000000;
                func_8015F408();
            }
        }
        goto final_adjustment;
    }

    if (!(((S_8015EDA8_1 *)arg2)->unk_14 & 0x40)) {
        if (((S_8015EDA8_1 *)arg2)->unk_2C == D_801620E0) {
            if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x100) {
                (*(u16 *)((u8 *)arg0 + 0x9E)) = 0;
            }
            count = (*(u16 *)((u8 *)arg0 + 0x9E));
            angle = (s32)((u32)count << 16) >> 16;
            call_arg = angle * 0xE3;
            count++;
            (*(u16 *)((u8 *)arg0 + 0x9E)) = count;
            (*(s32 *)((u8 *)arg0 + 0xA0)) = func_800644B8(call_arg) << 7;
            if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x103) {
                tail_base = D_801620E8;
                (*(u8 * *)((u8 *)arg2 + 0x2C)) = tail_base;
                tail_index = D_80083228;
                tail_state = ((S_8015EDA8_2 *)state)->unk_2A;
                tail_arg = arg2;
                tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                tail_value = &tail_base[tail_index];
                goto play_tail_value_2;
            }
        } else if (((S_8015EDA8_1 *)arg2)->unk_2C == D_801620E8) {
            count = (*(u16 *)((u8 *)arg0 + 0x9E));
            angle = (s32)((u32)count << 16) >> 16;
            call_arg = angle * 0xE3;
            count++;
            (*(u16 *)((u8 *)arg0 + 0x9E)) = count;
            (*(s32 *)((u8 *)arg0 + 0xA0)) = func_800644B8(call_arg) << 7;
            if (((S_8015EDA8_1 *)arg2)->unk_04.u16 == 0x103) {
                (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801620E0;
                tail_index = D_80083228;
                tail_state = ((S_8015EDA8_2 *)state)->unk_2A;
                tail_arg = arg2;
                tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                tail_value = &D_801620E0[tail_index];
play_tail_value_2:
                func_80047784(tail_arg, *tail_value, 0);
            }
        }
    }

    if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
        s32 height_work = -0x20;
        height = (*(s16 *)((u8 *)arg0 + 0x92));
        raw_height = (*(u16 *)((u8 *)arg0 + 0x92));
        if (height_work < height) {
            height_work = raw_height - 8;
            (*(s16 *)((u8 *)arg0 + 0x92)) = height_work;
        } else {
low_height_adjustment:
            height_work = height < -0x28;
            if (height_work) {
                height_work = raw_height + 8;
                (*(s16 *)((u8 *)arg0 + 0x92)) = height_work;
            }
        }
    }

final_adjustment:
    flags = ((S_8015EDA8_2 *)state)->unk_1C.u;
    if (flags & 0x40000000) {
        ((S_8015EDA8_2 *)state)->unk_1C.u = flags & 0xBFFFFFFF;
        ground = func_800BCB04(
            (((S_8015EDA8_1 *)arg2)->unk_24 << 6) | 0x20,
            (((S_8015EDA8_1 *)arg2)->unk_25 << 6) | 0x20,
            (s16)(((S_8015EDA8_2 *)state)->unk_88 - 0x20));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)arg0 + 0x92)) =
                (((S_8015EDA8_2 *)state)->unk_88 - ground) +
                (*(u16 *)((u8 *)arg0 + 0x92));
            ((S_8015EDA8_2 *)state)->unk_88 = ground;
        }
    }

    ((S_8015EDA8_0 *)arg1)->unk_0A = ((S_8015EDA8_2 *)state)->unk_88 +
        (*(u16 *)((u8 *)arg0 + 0x92)) - (*(u16 *)((u8 *)arg0 + 0xA2));
    ((S_8015EDA8_1 *)arg2)->unk_14 |= 0x40;
}
