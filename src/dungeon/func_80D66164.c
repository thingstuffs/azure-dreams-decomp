#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80171C0C(void) __attribute__((noreturn));
extern void func_80171EF4(void) __attribute__((noreturn));

extern u8 D_8006CCF8[];
extern s16 D_80083228[];
extern u16 D_80083462[];
extern u8 D_800E2348[];
extern void D_80171F1C(void *, void *, void *, void *);
extern Callback D_8017664C[];


typedef struct S_80171964_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171964_0;   /* motion in func_80171964 */

typedef struct S_80171964_1 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171964_1;   /* part in func_80171964 */

typedef struct S_80171964_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171964_2;   /* base in func_80171964 */

void func_80171964(void *arg0, void *arg1, void *arg2)
{
    void *obj = arg0;
    register void *motion ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *part ASM_REG("$20") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *base = obj;
    Callback first_callback;
    Callback dispatch_callback;
    s32 flags;
    s32 velocity;
    s16 floor;
    s32 floor_limit;
    s32 floor_value;
    register u32 raw_floor ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 part_flags;

    if (D_80083462[0] & 0x2000) {
        first_callback = (*(Callback *)((u8 *)obj + (0x8C)));
        if (first_callback == (Callback)D_80171F1C) {
            {
                void *entryArg0 = arg0;

                first_callback(entryArg0, arg1, arg2, entryArg0);
            }
            func_80171EF4();
        }
        (*(u8 *)((u8 *)obj + (0x71))) &= 0x7F;
        func_80171EF4();
    }

    ASM_KEEP(obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(motion);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(part);   /* MATCH pin: keeps a statement from moving across a call/branch */

    {
        s16 old_state = (s8)(*(u8 *)((u8 *)obj + (0x6D)));

        if (func_800A9E70(obj, motion, part, obj) != 0) {
            return;
        }
        dispatch_callback = (*(Callback *)((u8 *)obj + (0x8C)));
        if (dispatch_callback != 0) {
            dispatch_callback(obj, motion, part, obj);
        }
        D_8017664C[(*(u8 *)((u8 *)obj + (0x9A)))](obj, motion, part, obj);
        if ((s16)old_state != (s8)(*(u8 *)((u8 *)obj + (0x6D)))) {
            func_800AA36C(obj, motion, part, obj);
        }
    }

    ((S_80171964_0 *)motion)->unk_00.at00.v += ((S_80171964_0 *)motion)->unk_0C;
    ((S_80171964_0 *)motion)->unk_04.at00.v += ((S_80171964_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)obj + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
        ((S_80171964_0 *)motion)->unk_14 += (*(s8 *)((u8 *)obj + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)obj + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)obj + (0x9D))) = 0;
    }

    (*(s32 *)((u8 *)obj + (0x90))) += ((S_80171964_0 *)motion)->unk_14;
    part_flags = ((S_80171964_1 *)part)->unk_14;

    if (!(part_flags & 0x8000)) {
        s32 direction;
        s32 index;
        register s32 page_index ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register u8 *page_table ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        direction = (D_80083228[0] + ((S_80171964_2 *)base)->unk_2A + 0x100) >> 9;
        index = direction & 7;
        page_index = index;
        if ((*(s16 *)((u8 *)obj + (0x94))) != (s16)page_index) {
            func_80047738(part,
                (*(u8 *)((u8 *)(((S_80171964_1 *)part)->unk_2C) + (page_index))),
                ((S_80171964_1 *)part)->unk_04.s8);
            (*(s16 *)((u8 *)obj + (0x94))) = index;
        }
        page_table = D_8006CCF8;
        if (page_table[page_index] != 0) {
            ((S_80171964_1 *)part)->unk_14 |= 1;
        } else {
            ((S_80171964_1 *)part)->unk_14 &= 0xFFFE;
        }
        func_800A020C(((S_80171964_2 *)base)->unk_1C.s, (u8 *)part + 0xC);

        if (!(((S_80171964_2 *)base)->unk_1C.u & 0x20)) {
            if (!(((S_80171964_1 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
                {
                    u32 dead_page = 0xF7FF0000;

                    ASM_PAGEBASE_PIN(dead_page);   /* MATCH pin: retail delay-slot contents depend on it */
                }
                func_80171C0C();
            }
        } else {
            ((S_80171964_1 *)part)->unk_14 |= 0x7000;
            ((S_80171964_2 *)base)->unk_1C.u &= 0xFFFBFFFF;
        }

        flags = ((S_80171964_2 *)base)->unk_1C.u;
        flags &= 0xF7FFFFFF;
        ((S_80171964_2 *)base)->unk_1C.u = flags;
        flags &= 0x40000;
        if (!flags) {
            goto clear_velocity;
        }

        if (!(((S_80171964_1 *)part)->unk_14 & 0x40) &&
            ((S_80171964_1 *)part)->unk_2C == D_800E2348) {
            if (((S_80171964_1 *)part)->unk_04.u16 == 0x400) {
                (*(u16 *)((u8 *)obj + (0x9E))) = 0;
            }
            {
                u16 counter = (*(u16 *)((u8 *)obj + (0x9E)));

                (*(u16 *)((u8 *)obj + (0x9E))) = counter + 1;
                (*(s32 *)((u8 *)obj + (0xA0))) = -func_800644B8((s16)counter * 0xC3) << 7;
            }
        }
        if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
            floor_limit = -0x20;
            floor_value = *(s16 *)((u8 *)obj + 0x92);
            raw_floor = *(volatile u16 *)((u8 *)obj + 0x92);
            if (floor_limit < floor_value) {
                floor_limit = raw_floor - 8;
                *(s16 *)((u8 *)obj + 0x92) = floor_limit;
                goto common_tail;
            }
            goto raise_floor;
        }
        goto common_tail;
    }

    if (part_flags & 0x800) {
        ((S_80171964_1 *)part)->unk_14 = part_flags & 0x8FFF;
    } else {
        ((S_80171964_1 *)part)->unk_14 = part_flags | 0x7000;
    }
    flags = ((S_80171964_2 *)base)->unk_1C.u;
    flags &= 0xF7FFFFFF;
    ((S_80171964_2 *)base)->unk_1C.u = flags;
    flags &= 0x40000;
    if (!flags) {
clear_velocity:
        velocity = (*(s32 *)((u8 *)obj + (0xA0)));
        (*(u16 *)((u8 *)obj + (0x9E))) = 0;
        (*(s32 *)((u8 *)obj + (0xA0))) = 0;
        (*(s32 *)((u8 *)obj + (0x90))) -= velocity;
        if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
            floor = func_800BCB04(((S_80171964_0 *)motion)->unk_00.at02.v,
                                  ((S_80171964_0 *)motion)->unk_04.at02.v,
                                  (s16)(((S_80171964_2 *)base)->unk_88 - 0x20)) -
                    ((S_80171964_2 *)base)->unk_88;
            if (floor < (*(s16 *)((u8 *)obj + (0x92)))) {
                (*(s16 *)((u8 *)obj + (0x92))) = floor;
                (*(u8 *)((u8 *)obj + (0x9D))) = 0;
                ((S_80171964_0 *)motion)->unk_14 = 0;
                ((S_80171964_2 *)base)->unk_1C.u |= 0x08000000;
                goto common_tail;
            }
        }
        goto common_tail;
    }

    if (!(((S_80171964_1 *)part)->unk_14 & 0x40) &&
        ((S_80171964_1 *)part)->unk_2C == D_800E2348) {
        if (((S_80171964_1 *)part)->unk_04.u16 == 0x400) {
            (*(u16 *)((u8 *)obj + (0x9E))) = 0;
        }
        {
            u16 counter = (*(u16 *)((u8 *)obj + (0x9E)));

            (*(u16 *)((u8 *)obj + (0x9E))) = counter + 1;
            (*(s32 *)((u8 *)obj + (0xA0))) = -func_800644B8((s16)counter * 0xC3) << 7;
        }
    }
    if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
        floor_limit = -0x20;
        floor_value = *(s16 *)((u8 *)obj + 0x92);
        raw_floor = *(volatile u16 *)((u8 *)obj + 0x92);
        if (floor_limit < floor_value) {
            floor_limit = raw_floor - 8;
            *(s16 *)((u8 *)obj + 0x92) = floor_limit;
        } else {
raise_floor:
            floor_limit = floor_value < -0x28;
            if (floor_limit) {
                floor_limit = raw_floor + 8;
                *(s16 *)((u8 *)obj + 0x92) = floor_limit;
            }
        }
    }

common_tail:
    flags = ((S_80171964_2 *)base)->unk_1C.u;
    if (flags & 0x40000000) {
        ((S_80171964_2 *)base)->unk_1C.u = flags & 0xBFFFFFFF;
        floor = func_800BCB04(
            (((S_80171964_1 *)part)->unk_24 << 6) | 0x20,
            (((S_80171964_1 *)part)->unk_25 << 6) | 0x20,
            (s16)(((S_80171964_2 *)base)->unk_88 - 0x20));
        if (floor < 0x200) {
            (*(u16 *)((u8 *)obj + (0x92))) += ((S_80171964_2 *)base)->unk_88 - floor;
            ((S_80171964_2 *)base)->unk_88 = floor;
        }
    }
    if ((*(u8 *)((u8 *)obj + (0x9A))) != 0x18) {
        ((S_80171964_0 *)motion)->unk_0A =
            ((S_80171964_2 *)base)->unk_88 + (*(u16 *)((u8 *)obj + (0x92))) -
            (*(u16 *)((u8 *)obj + (0xA2)));
    } else {
        ((S_80171964_0 *)motion)->unk_0A = (*(u16 *)((u8 *)obj + (0x92))) - (*(u16 *)((u8 *)obj + (0xA2)));
    }
    ((S_80171964_1 *)part)->unk_14 |= 0x40;
}
