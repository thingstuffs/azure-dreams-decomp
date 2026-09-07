#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[9];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_80171058[];
extern u8 D_80174880[9];
extern Callback D_80174900[];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_80170C0C(void) __attribute__((noreturn));
extern void func_80170CB4(void) __attribute__((noreturn));
extern void func_80170D20(void) __attribute__((noreturn));
extern void func_80170F8C() __attribute__((noreturn));
extern void func_80171030(void) __attribute__((noreturn));

void func_80170A78(void *arg0, void *arg1, void *arg2)
{
    void *obj = arg0;
    void *motion = arg1;
    void *part = arg2;
    register void *state ASM_REG("$18") = arg0;
    register s32 work ASM_REG("$16");
    register s32 direction ASM_REG("$19");
    register u32 raw_work ASM_REG("$2");
    Callback callback;
    s32 floor_y;
    s16 delta;
    u16 part_flags;
    register u16 count ASM_REG("$3");
    register s32 flags ASM_REG("$3");
    s32 amount;
    u8 collision;

    if (*(u16 *)(D_80083460 + 2) & 0x2000) {
        callback = FIELD(arg0, Callback, 0x8C);
        if (callback == (Callback)D_80171058) {
            register void *entry_obj ASM_REG("$4") = arg0;
            ASM_KEEP(entry_obj);
            callback(entry_obj, arg1, arg2, entry_obj);
            return func_80171030();
        } else {
            return (FIELD(arg0, u8, 0x71) &= 0x7F, func_80171030());
        }
    }

#define arg0 obj
#define arg1 motion
#define arg2 part

    ASM_KEEP(obj);
    raw_work = *(volatile u8 *)((u8 *)arg0 + 0x6D);
    raw_work <<= 24;
    work = (s32)raw_work >> 24;
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    {
        register Callback callback2 ASM_REG("$2");
        callback2 = FIELD(arg0, Callback, 0x8C);
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, arg0);
        }
    }
    D_80174900[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);
    raw_work = (u32)work << 16;
    if (((s32)raw_work >> 16) != FIELD(arg0, s8, 0x6D)) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    {
        s32 old_x = FIELD(arg1, s32, 0);
        s32 temp_a0 = FIELD(arg1, s32, 0xC);
        s32 old_y = FIELD(arg1, s32, 4);
        s32 temp_a1 = FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 0) = old_x + temp_a0;
        FIELD(arg1, s32, 4) = old_y + temp_a1;

        if (!(FIELD(arg0, s32, 0x1C) & 0x40000) &&
            !(FIELD(arg0, u16, 0x98) & 8)) {
            FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
            FIELD(arg0, u8, 0x9D) += 1;
            return func_80170C0C();
        } else {
            FIELD(arg0, u8, 0x9D) = 0;
            ASM_KEEP(obj);
        }
    }

    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);
    part_flags = FIELD(arg2, u16, 0x14);
    if (!(part_flags & 0x8000)) {
        raw_work = *(s16 *)((u8 *)D_80083460 - 0x238) +
            FIELD(state, s16, 0x2A) + 0x100;
        direction = ((s32)raw_work >> 9) & 7;
        work = direction;
        if (FIELD(arg0, s16, 0x94) != work) {
            func_80047738(arg2,
                *(u8 *)(FIELD(arg2, u8 *, 0x2C) + work),
                FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = direction;
        }
        collision = D_8006CCF8[work];
        ASM_KEEP(work);
        if (collision != 0) {
            raw_work = *(volatile u16 *)((u8 *)arg2 + 0x14) | 1;
            ASM_TAILSLOT_PIN(raw_work);
            return func_80170CB4();
        } else {
            FIELD(arg2, u16, 0x14) &= 0xFFFE;
        }

        func_800A020C(FIELD(state, s32, 0x1C), (u8 *)arg2 + 0xC);
        if (!(FIELD(state, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                raw_work = 0xF7FF0000;
                ASM_PAGEBASE_PIN(raw_work);
                return func_80170D20();
            }
        } else {
            FIELD(arg2, u16, 0x14) |= 0x7000;
            FIELD(state, s32, 0x1C) &= 0xFFFBFFFF;
        }
        raw_work = 0xF7FFFFFF;
        flags = FIELD(state, s32, 0x1C) & raw_work;
        FIELD(state, s32, 0x1C) = flags;
        if (!(flags & 0x40000)) {
            goto reset_height;
        }

        if (!(FIELD(arg2, u16, 0x14) & 0x40) &&
            FIELD(arg2, void *, 0x2C) == D_80174880) {
            count = FIELD(arg0, u16, 0xB2);
            FIELD(arg0, u16, 0xB2) = count + 1;
            FIELD(arg0, s32, 0xA4) += func_800644B8((s16)count * 0xAA) << 5;
        }
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            delta = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                        (s16)(FIELD(state, u16, 0x88) - 0x20)) -
                    FIELD(state, u16, 0x88);
            floor_y = FIELD(arg0, s16, 0x92);
            if (floor_y > delta - 0x18) {
                FIELD(arg0, s16, 0x92) = FIELD(arg0, s16, 0x92) - 8;
                return func_80170F8C(floor_y, delta);
            }
            if (floor_y < delta - 0x20) {
                FIELD(arg0, s16, 0x92) = FIELD(arg0, u16, 0x92) + 8;
            }
        }
        goto finish_height;
    }

    if (part_flags & 0x800) {
        FIELD(arg2, u16, 0x14) = part_flags & 0x8FFF;
    } else {
        FIELD(arg2, u16, 0x14) = part_flags | 0x7000;
    }
    raw_work = 0xF7FFFFFF;
    flags = FIELD(state, s32, 0x1C) & raw_work;
    FIELD(state, s32, 0x1C) = flags;
    if (!(flags & 0x40000)) {
reset_height:
        amount = FIELD(arg0, s32, 0xA4);
        FIELD(arg0, u16, 0xB2) = 0;
        FIELD(arg0, s32, 0xA4) = 0;
        FIELD(arg0, s32, 0x90) -= amount;
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            delta = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                        (s16)(FIELD(state, u16, 0x88) - 0x20)) -
                    FIELD(state, u16, 0x88);
            if (delta < FIELD(arg0, s16, 0x92)) {
                FIELD(arg0, s16, 0x92) = delta;
                FIELD(arg0, u8, 0x9D) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(state, s32, 0x1C) |= 0x08000000;
                return func_80170F8C();
            }
        }
        goto finish_height;
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x40) &&
        FIELD(arg2, void *, 0x2C) == D_80174880) {
        count = FIELD(arg0, u16, 0xB2);
        FIELD(arg0, u16, 0xB2) = count + 1;
        FIELD(arg0, s32, 0xA4) += func_800644B8((s16)count * 0xAA) << 5;
    }
    if (!(FIELD(arg0, u16, 0x98) & 8)) {
        delta = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                    (s16)(FIELD(state, u16, 0x88) - 0x20)) -
                FIELD(state, u16, 0x88);
        floor_y = FIELD(arg0, s16, 0x92);
        if (floor_y > delta - 0x18) {
            FIELD(arg0, s16, 0x92) = FIELD(arg0, s16, 0x92) - 8;
            goto finish_height;
        }
        if (floor_y < delta - 0x20) {
            FIELD(arg0, s16, 0x92) = FIELD(arg0, u16, 0x92) + 8;
        }
    }

finish_height:
    if (FIELD(state, s32, 0x1C) & 0x40000000) {
        FIELD(state, s32, 0x1C) &= 0xBFFFFFFF;
        delta = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
            (FIELD(arg2, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(state, u16, 0x88) - 0x20));
        if ((s16)delta < 0x200) {
            FIELD(arg0, s16, 0x92) += FIELD(state, u16, 0x88) - delta;
            FIELD(state, u16, 0x88) = delta;
        }
    }
    FIELD(arg1, s16, 0xA) = FIELD(state, u16, 0x88) +
        FIELD(arg0, u16, 0x92) - FIELD(arg0, u16, 0xA6);
    FIELD(arg2, u16, 0x14) |= 0x40;
}
