#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

void func_80171964(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$21") = arg1;
    register void *part ASM_REG("$20") = arg2;
    register void *base ASM_REG("$18") = obj;
    Callback first_callback;
    Callback dispatch_callback;
    s32 flags;
    s32 velocity;
    s16 floor;
    s32 floor_limit;
    register s32 floor_value ASM_REG("$4");
    register u32 raw_floor ASM_REG("$3");
    u16 part_flags;

    if (D_80083462[0] & 0x2000) {
        first_callback = FIELD(obj, Callback, 0x8C);
        if (first_callback == (Callback)D_80171F1C) {
            {
                register void *entryArg0 ASM_REG("$4") = arg0;

                ASM_KEEP(entryArg0);
                first_callback(entryArg0, arg1, arg2, entryArg0);
            }
            func_80171EF4();
        }
        FIELD(obj, u8, 0x71) &= 0x7F;
        func_80171EF4();
    }

    ASM_KEEP(obj);
    ASM_KEEP(motion);
    ASM_KEEP(part);
    ASM_KEEP(base);

    {
        s16 old_state = (s8)FIELD(obj, u8, 0x6D);

        if (func_800A9E70(obj, motion, part, obj) != 0) {
            return;
        }
        dispatch_callback = FIELD(obj, Callback, 0x8C);
        if (dispatch_callback != 0) {
            dispatch_callback(obj, motion, part, obj);
        }
        D_8017664C[FIELD(obj, u8, 0x9A)](obj, motion, part, obj);
        if ((s16)old_state != (s8)FIELD(obj, u8, 0x6D)) {
            func_800AA36C(obj, motion, part, obj);
        }
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (!(FIELD(obj, u32, 0x1C) & 0x40000) &&
        !(FIELD(obj, u16, 0x98) & 8)) {
        FIELD(motion, s32, 0x14) += FIELD(obj, s8, 0x9D) * 0x14000;
        FIELD(obj, u8, 0x9D)++;
    } else {
        FIELD(obj, u8, 0x9D) = 0;
    }

    FIELD(obj, s32, 0x90) += FIELD(motion, s32, 0x14);
    part_flags = FIELD(part, u16, 0x14);

    if (!(part_flags & 0x8000)) {
        s32 direction;
        s32 index;
        register s32 page_index ASM_REG("$16");
        register u8 *page_table ASM_REG("$2");

        direction = (D_80083228[0] + FIELD(base, s16, 0x2A) + 0x100) >> 9;
        ASM_KEEP(direction);
        index = direction & 7;
        page_index = index;
        if (FIELD(obj, s16, 0x94) != (s16)page_index) {
            func_80047738(part,
                FIELD(FIELD(part, u8 *, 0x2C), u8, page_index),
                FIELD(part, s8, 4));
            FIELD(obj, s16, 0x94) = index;
        }
        page_table = D_8006CCF8;
        if (page_table[page_index] != 0) {
            FIELD(part, u16, 0x14) |= 1;
        } else {
            FIELD(part, u16, 0x14) &= 0xFFFE;
        }
        func_800A020C(FIELD(base, s32, 0x1C), (u8 *)part + 0xC);

        if (!(FIELD(base, u32, 0x1C) & 0x20)) {
            if (!(FIELD(part, u16, 0x14) & 0x40)) {
                func_800478B8(part);
                {
                    register u32 dead_page ASM_REG("$2") = 0xF7FF0000;

                    ASM_PAGEBASE_PIN(dead_page);
                }
                func_80171C0C();
            }
        } else {
            FIELD(part, u16, 0x14) |= 0x7000;
            FIELD(base, u32, 0x1C) &= 0xFFFBFFFF;
        }

        flags = FIELD(base, u32, 0x1C);
        flags &= 0xF7FFFFFF;
        FIELD(base, u32, 0x1C) = flags;
        flags &= 0x40000;
        if (!flags) {
            goto clear_velocity;
        }

        if (!(FIELD(part, u16, 0x14) & 0x40) &&
            FIELD(part, u8 *, 0x2C) == D_800E2348) {
            if (FIELD(part, u16, 4) == 0x400) {
                FIELD(obj, u16, 0x9E) = 0;
            }
            {
                u16 counter = FIELD(obj, u16, 0x9E);

                FIELD(obj, u16, 0x9E) = counter + 1;
                FIELD(obj, s32, 0xA0) = -func_800644B8((s16)counter * 0xC3) << 7;
            }
        }
        if (!(FIELD(obj, u16, 0x98) & 8)) {
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
        FIELD(part, u16, 0x14) = part_flags & 0x8FFF;
    } else {
        FIELD(part, u16, 0x14) = part_flags | 0x7000;
    }
    flags = FIELD(base, u32, 0x1C);
    flags &= 0xF7FFFFFF;
    FIELD(base, u32, 0x1C) = flags;
    flags &= 0x40000;
    if (!flags) {
clear_velocity:
        velocity = FIELD(obj, s32, 0xA0);
        FIELD(obj, u16, 0x9E) = 0;
        FIELD(obj, s32, 0xA0) = 0;
        FIELD(obj, s32, 0x90) -= velocity;
        if (!(FIELD(obj, u16, 0x98) & 8)) {
            floor = func_800BCB04(FIELD(motion, u16, 2),
                                  FIELD(motion, u16, 6),
                                  (s16)(FIELD(base, u16, 0x88) - 0x20)) -
                    FIELD(base, u16, 0x88);
            if (floor < FIELD(obj, s16, 0x92)) {
                FIELD(obj, s16, 0x92) = floor;
                FIELD(obj, u8, 0x9D) = 0;
                FIELD(motion, s32, 0x14) = 0;
                FIELD(base, u32, 0x1C) |= 0x08000000;
                goto common_tail;
            }
        }
        goto common_tail;
    }

    if (!(FIELD(part, u16, 0x14) & 0x40) &&
        FIELD(part, u8 *, 0x2C) == D_800E2348) {
        if (FIELD(part, u16, 4) == 0x400) {
            FIELD(obj, u16, 0x9E) = 0;
        }
        {
            u16 counter = FIELD(obj, u16, 0x9E);

            FIELD(obj, u16, 0x9E) = counter + 1;
            FIELD(obj, s32, 0xA0) = -func_800644B8((s16)counter * 0xC3) << 7;
        }
    }
    if (!(FIELD(obj, u16, 0x98) & 8)) {
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
    flags = FIELD(base, u32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(base, u32, 0x1C) = flags & 0xBFFFFFFF;
        floor = func_800BCB04(
            (FIELD(part, u8, 0x24) << 6) | 0x20,
            (FIELD(part, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(base, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            FIELD(obj, u16, 0x92) += FIELD(base, u16, 0x88) - floor;
            FIELD(base, u16, 0x88) = floor;
        }
    }
    if (FIELD(obj, u8, 0x9A) != 0x18) {
        FIELD(motion, u16, 0xA) =
            FIELD(base, u16, 0x88) + FIELD(obj, u16, 0x92) -
            FIELD(obj, u16, 0xA2);
    } else {
        FIELD(motion, u16, 0xA) = FIELD(obj, u16, 0x92) - FIELD(obj, u16, 0xA2);
    }
    FIELD(part, u16, 0x14) |= 0x40;
}
