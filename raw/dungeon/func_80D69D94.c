#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2348[];
extern u8 D_800E23B8[];
extern u8 D_800E23C0[];
extern void *const D_80170920[];
extern s32 D_80171F1C;

extern void func_80047784(void *, u8, s32);
extern s32 func_80069EF8(void);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_800A4E2C(u8 *, u8 *);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s32);
extern void func_800D6DC0(void *, void *, void *, void *);
extern void func_80170A44(void *, void *, void *, void *);
extern void func_80170BB8(void *, void *, void *, void *, s32);
extern void func_80171010(void *, void *, void *, s32, s32, s32);
extern s32 func_8017165C(s32);

void func_80175594(void *arg0, void *arg1, void *entity_in, void *arg3)
{
    register void *arg2 ASM_REG("$19") = entity_in;
    register void *object ASM_REG("$23");
    s32 counter;
    s32 attempts;
    s32 random_x4;
    s32 random_x5;
    s16 random_y;
    s16 result;
    register s32 dx ASM_REG("$2");
    register s32 dy ASM_REG("$3");
    s32 entity_y;
    u8 old_x;
    u8 old_y;
    u8 *world;
    u8 *table;

    ASM_KEEP(arg2);

    {
        static void *const sw_keep[] = {
            &&case_0, &&case_1, &&case_2, &&case_3,
            &&case_4, &&case_5, &&case_6, &&case_7
        };
        u32 swi = FIELD(arg0, u8, 0x9B);

        if (swi >= 8) {
            goto done;
        }
        object = arg3;
        ASM_KEEP(object);
        (void)sw_keep;
        goto *D_80170920[swi];
    }

case_0:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 7;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        goto done;
    }
    if (FIELD(arg0, s32, 0xA0) <= 0x6FFFF) {
        goto done;
    }
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(object, u32, 0x1C) &= ~0x40000;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, u16, 0x92) -= 8;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg0, u16, 0xB6) =
        FIELD(arg1, u16, 0x0A) + FIELD(arg0, u16, 0x92);
    goto done;

case_1:
    FIELD(arg2, u8 *, 0x2C) = D_800E23B8;
    func_80047784(arg2,
        D_800E23B8[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    ASM_SCHED_BARRIER();
    goto next_state;

case_2:
    if (++FIELD(arg0, s16, 0x96) < 9) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_800E23C0;
    func_80047784(arg2,
        D_800E23C0[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    goto next_state;

case_3:
    if (FIELD(arg0, s16, 0x96)++ < 3) {
        goto done;
    }
    ASM_SCHED_BARRIER();
    goto next_state;

case_4:
    if (FIELD(arg0, s16, 0x96)++ < 0xB) {
        goto done;
    }
    counter = 0;
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, s32, 0xAC) = 0;
    do {
        random_x4 = (s16)(func_8017165C(0x2C) - 0x16);
        random_y = func_8017165C(0x2C) - 0x16;
        func_80171010(arg0, arg1, arg2, random_x4, random_y, 0x1E);
        counter++;
    } while (counter < 6);
    func_800D6DC0(arg0, arg1, arg2, object);
    goto done;

case_5:
    switch (FIELD(arg0, s16, 0x96)) {
    case 0:
        FIELD(arg1, s32, 0x14) = -0x140000;
        FIELD(arg0, s32, 0xAC) = 0x30000;
        break;
    case 6:
        FIELD(arg1, s32, 0x14) = -0x180000;
        FIELD(arg0, s32, 0xAC) = -0x10000;
        break;
    case 12:
        FIELD(arg0, s32, 0xAC) = -0x20000;
        break;
    }
    FIELD(arg1, s32, 0x14) += FIELD(arg0, s32, 0xAC);

    if (FIELD(arg0, s16, 0x96) < 2) {
        counter = 0;
        do {
            random_x5 = (s16)((func_80069EF8() & 0x1F) - 0x10);
            random_y = (func_80069EF8() & 0x1F) - 0x10;
            func_80171010(arg0, arg1, arg2, random_x5, random_y, 0x1E);
            counter++;
        } while (counter < 4);
    }
    if (FIELD(arg0, s16, 0x96) == 1) {
        func_80170BB8(arg0, arg1, arg2, object, 1);
        func_800A56E0(0x80A);
    }
    if (FIELD(arg0, s16, 0x96) == 2) {
        func_80170A44(arg0, arg1, arg2, object);
    }
    if (FIELD(arg0, s16, 0x96) == 6) {
        func_80170BB8(arg0, arg1, arg2, object, 0x1A);
        func_800A56E0(0x705);
    }
    if (FIELD(arg0, s16, 0x96)++ < 0x2E) {
        goto done;
    }
    goto next_state;

case_6:
    FIELD(arg1, u16, 0x0A) = FIELD(arg0, u16, 0xB6);

next_state:
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

case_7:
    func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
        (FIELD(object, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    attempts = 0x20;
    world = D_80082E80;
    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    do {
        do {
            result = func_800A4E2C((u8 *)arg2 + 0x24, (u8 *)arg2 + 0x25);
        } while (result < 0);

        dx = world[0x24];
        dy = FIELD(arg2, u8, 0x24);
        entity_y = FIELD(arg2, u8, 0x25);
        ASM_SCHED_BARRIER();
        dx -= dy;
        dy = world[0x25];
        if (dx < 0) {
            dx = -dx;
        }
        dy -= entity_y;
        if (dy < 0) {
            dy = -dy;
        }
        if (dx + dy >= 0x21) {
            goto coordinates_ready;
        }
    } while (--attempts >= 0);
    FIELD(arg2, u8, 0x24) = old_x;
    FIELD(arg2, u8, 0x25) = old_y;

coordinates_ready:
    FIELD(arg1, s16, 0x02) = (FIELD(arg2, u8, 0x24) << 6) + 0x20;
    FIELD(arg1, s16, 0x06) = (FIELD(arg2, u8, 0x25) << 6) + 0x20;
    result = func_800BCB04(FIELD(arg1, u16, 0x02), FIELD(arg1, u16, 0x06),
        -0x200);
    result -= 0x11;
    ASM_SCHED_BARRIER();
    attempts = -0x20;
    FIELD(arg1, s16, 0x0A) = result;
    FIELD(arg0, s16, 0x92) = attempts;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(object, s16, 0x88) = -0x200;
    result = func_800BCB04(
        (FIELD(arg2, u8, 0x24) << 6) | 0x20,
        (FIELD(arg2, u8, 0x25) << 6) | 0x20,
        -0x200);
    FIELD(object, s16, 0x88) = result;

    func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
        (FIELD(object, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object);
    func_800AD594(object, 0x1000);
    FIELD(arg0, s32 *, 0x8C) = &D_80171F1C;
    D_8008346C = 0;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, s16, 0x92) = attempts;
    FIELD(object, u32, 0x1C) |= 0x40000;
    FIELD(arg0, u16, 0x98) |= 8;

    table = D_800E2348;
    if (FIELD(arg2, u8 *, 0x2C) != table) {
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg2, u8, 5) = 1;
        FIELD(arg0, s16, 0xA2) = 0;
        FIELD(arg0, s16, 0x9E) = 0;
    }
    FIELD(object, u16, 0x46) &= 0x7FFF;

done:
    return;
}

#undef FIELD
