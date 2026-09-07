#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 D_80010234;
extern s32 D_80012090;
extern s16 D_80081468[3];
extern s16 D_8008146C;
extern u8 D_80082E6B;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_80083780[];
extern s32 D_80083788;
extern u16 D_8008378A;
extern s16 D_800DCED4[];
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 *D_800E3D7C;
extern u8 D_80170940[];
extern u8 D_80170950[];
extern u8 D_80170988[];
extern u8 D_80170994[];
extern u8 D_801709B8[];
extern void *const D_801709F0[];
extern s32 D_80171F1C;

extern void func_80040AA0(u8, s16 *);
extern s32 func_800429E4(void *);
extern void func_80047784(void *, u8, s32);
extern void func_800481E0(void);
extern void func_800945E8(void *);
extern void func_800948BC(void);
extern void func_80094E34(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A6780(void);
extern void func_800AD594(void *, s32);
extern void func_800C542C(void *, s16, s32, s32);

void func_80175CD8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 counter;
    s32 value;
    s32 target_x;
    s32 target_y;
    s32 target_z;
    s32 timer1;
    s32 timer8;
    s32 direction;
    s32 saved;
    u8 *world0;
    u8 *world1;
    u8 *object;

    {
        static void *const sw_keep[] = {
            &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
            &&state_5, &&state_6, &&state_7, &&state_8, &&state_9,
            &&done, &&done, &&done, &&done, &&done, &&done,
            &&done, &&done, &&done, &&done, &&done
        };
        u32 state = FIELD(arg0, u8, 0x9B);

        if (state >= 0x15) {
            goto done;
        }
        (void)sw_keep;
        goto *D_801709F0[state];
    }

state_0:
    {
        register u8 *pin_a0 ASM_REG("$4");
        register s32 pin_a1 ASM_REG("$5");
        register s32 dx ASM_REG("$2");
        register s32 dy ASM_REG("$3");
        u8 w24;
        u8 c24;
        u8 c25;
        u8 w25;

        pin_a0 = arg3;
        world0 = D_80082E80;
        ASM_KEEP(world0);
        pin_a1 = 0x2000;
        ASM_KEEP(pin_a1);
        w24 = world0[0x24];
        c24 = FIELD(arg2, u8, 0x24);
        c25 = FIELD(arg2, u8, 0x25);
        dx = w24;
        dx -= c24;
        w25 = world0[0x25];
        if (dx < 0) {
            dx = -dx;
        }
        dy = w25;
        dy -= c25;
        if (dy < 0) {
            dy = -dy;
        }
        FIELD(arg0, s16, 0x96) = ((dx + dy) * 4) + 9;
        FIELD(arg0, u8, 0x9B)++;
        func_800AD594(pin_a0, pin_a1);
    }

    if (world0[0x24] == FIELD(arg2, u8, 0x24)) {
        if (world0[0x25] > FIELD(arg2, u8, 0x25)) {
            direction = 2;
        } else {
            direction = 6;
        }
    } else if (world0[0x25] == FIELD(arg2, u8, 0x25)) {
        direction = (FIELD(arg2, u8, 0x24) >= world0[0x24]) * 4;
    } else if (FIELD(arg2, u8, 0x24) < world0[0x24]) {
        if (FIELD(arg2, u8, 0x25) < world0[0x25]) {
            direction = 1;
        } else {
            direction = 7;
        }
    } else if (FIELD(arg2, u8, 0x25) < world0[0x25]) {
        direction = 3;
    } else {
        direction = 5;
    }
    FIELD(arg3, s16, 0x2A) = direction << 9;

    if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
        if (FIELD(arg3, u8, 0x11) >= D_8008146C) {
            counter = 0;
            do {
                object = *(u8 **)(D_800E3D7C + 0xAC + counter * 4);
                if ((object != 0) && (object != (u8 *)arg3)) {
                    value = func_800429E4(object);
                    func_800C542C(object, D_800DCED4[value], (s16)counter, 0);
                }
                counter++;
            } while (counter < 2);
        }
    }

state_1:
    world1 = D_80082E80;
    target_x = ((world1[0x24] << 6) + 0x20) << 16;
    target_y = ((world1[0x25] << 6) + 0x20) << 16;
    target_z = D_80083788 - 0x600000;
    timer1 = FIELD(arg0, s16, 0x96);
    if (timer1 >= 0xE) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer1 - 9);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 9);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 9);
    } else if (timer1 >= 0xB) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer1 - 7);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 7);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 7);
    } else if (timer1 >= 5) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer1 - 2);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 2);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 2);
    } else {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / timer1;
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            FIELD(arg0, s16, 0x96);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            FIELD(arg0, s16, 0x96);
    }
    goto decrement_timer;

state_2:
    FIELD(arg2, u8 *, 0x2C) = D_800E2368;
    value = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_800E2368[value & 7], 0);
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_80094E34();
    goto done;

state_3:
    {
        u16 old_timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, s16, 0x96) = old_timer + 1;
        if ((s16)old_timer < 7) {
            goto done;
        }
    }
    FIELD(arg0, u8, 0x9B)++;
    {
        u8 *held = D_800E3D7C;

        FIELD(arg0, s16, 0x96) = 0;
        FIELD(held, u32, 0x14) |= 0x100000;
    }
    func_800A56E0(0x603);
    goto done;

state_4:
    {
        u8 *globals = D_80083780;
        s32 accel = (s32)0xFFF40000;

        FIELD(arg1, s32, 0x14) = accel;
        FIELD(globals, s32, 8) += accel;
    }
    {
        u16 old_timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, s16, 0x96) = old_timer + 1;
        if ((s16)old_timer < 0x1B) {
            goto done;
        }
    }
    FIELD(arg0, s16, 0x96) = 0;
    ASM_KEEP(arg0);
    if ((D_80012090 == 0) && (D_8008146C == 0x28)) {
        FIELD(arg0, u8, 0x9B) = 7;
    } else if (FIELD(arg3, u8, 0x11) >= D_8008146C) {
        FIELD(arg0, u8, 0x9B)++;
    } else {
        FIELD(arg0, u8, 0x9B) = 7;
    }
    goto done;

state_5:
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_6:
    func_800945E8(D_800E3D7C);
    func_800948BC();
    func_800A6780();
    {
        register u8 *page8 ASM_REG("$2");
        register u8 *page_1 ASM_REG("$6");
        register s16 *counts ASM_REG("$5");
        register u8 call_a0 ASM_REG("$4");
        register s32 count32 ASM_REG("$2");
        register u16 count16 ASM_REG("$3");

        page8 = (u8 *)0x80080000;
        ASM_KEEP(page8);
        page_1 = (u8 *)0x80010000;
        ASM_KEEP(page_1);
        counts = D_80081468;
        call_a0 = page8[0x2E6B];
        count32 = *(s32 *)(page_1 + 0x234);
        count16 = *(u16 *)((u8 *)counts + 4);
        count32++;
        count16++;
        *(s32 *)(page_1 + 0x234) = count32;
        *(u16 *)((u8 *)counts + 4) = count16;
        func_80040AA0(call_a0, counts);
    }
    func_800481E0();
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B) = 0x14;
    goto clear_object_flag;

state_7:
    {
        u8 *global_ptr = D_800E3D7C;
        u8 *globals;
        u32 masked;
        u16 height;

        ASM_KEEP(global_ptr);
        masked = FIELD(global_ptr, u32, 0x14) & 0xFFEFFFFF;
        ASM_KEEP(masked);
        globals = D_80083498;
        globals += 0x20;
        FIELD(global_ptr, u32, 0x14) = masked;
        height = D_8008378A - FIELD(globals, u16, 0x88);
        FIELD(global_ptr, s16, 0x92) = height;
        FIELD(globals, s16, 0x88) = height;
        FIELD(globals, u32, 0x1C) |= 0x40000000;
    }
    FIELD(arg0, s16, 0x96) = 0x28;
    FIELD(arg0, u8, 0x9B)++;

    if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
        saved = func_800990FC();
        value = func_80099194(D_80170940, saved);
        value = func_8009929C(0xA, value);
        value = func_80099194(D_80170950, value);
        value = func_8009929C(0xA, value);
        value = func_80099194(D_80170988, value);
        value = func_80099734(arg3, value);
        value = func_80099194(D_80170994, value);
    } else {
        saved = func_800990FC();
        value = func_80099194(D_801709B8, saved);
    }
    func_80099290(value);
    func_800A5720(saved);

state_8:
    target_x = ((FIELD(arg2, u8, 0x24) << 6) + 0x20) << 16;
    target_y = ((FIELD(arg2, u8, 0x25) << 6) + 0x20) << 16;
    target_z = (FIELD(arg0, s16, 0xB4) - 0x20) << 16;
    timer8 = FIELD(arg0, s16, 0x96);
    if (timer8 >= 0xE) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer8 - 9);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 9);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 9);
    } else if (timer8 >= 0xB) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer8 - 7);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 7);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 7);
    } else if (timer8 >= 5) {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / (timer8 - 2);
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            (FIELD(arg0, s16, 0x96) - 2);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            (FIELD(arg0, s16, 0x96) - 2);
    } else {
        FIELD(arg1, s32, 0x0C) = (target_x - FIELD(arg1, s32, 0)) / timer8;
        FIELD(arg1, s32, 0x10) = (target_y - FIELD(arg1, s32, 4)) /
            FIELD(arg0, s16, 0x96);
        FIELD(arg1, s32, 0x14) = (target_z - FIELD(arg0, s32, 0x90)) /
            FIELD(arg0, s16, 0x96);
    }

decrement_timer:
    value = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = value;
    if ((value << 16) != 0) {
        goto done;
    }
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    goto done;

state_9:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, s32 *, 0x8C) = &D_80171F1C;
    FIELD(arg0, u8, 0x9A) = 0xE;
    D_8008346C = 0;
    FIELD(arg3, u32, 0x1C) |= 0x40000;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg2, u8 *, 0x2C) = D_800E2348;
    value = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_800E2348[value & 7], 0);
    FIELD(arg2, u8, 5) = 1;
    FIELD(arg0, s16, 0xA2) = 0;
    FIELD(arg0, s16, 0x9E) = 0;
    FIELD(arg0, s16, 0x92) = -0x20;
    FIELD(arg3, u16, 0x88) = FIELD(arg0, u16, 0xB4);
    FIELD(arg1, s16, 2) = (FIELD(arg2, u8, 0x24) << 6) + 0x20;
    FIELD(arg1, s16, 6) = (FIELD(arg2, u8, 0x25) << 6) + 0x20;
    FIELD(arg1, s16, 0x0A) = FIELD(arg3, u16, 0x88) +
        FIELD(arg0, u16, 0x92) - FIELD(arg0, u16, 0xA2);

clear_object_flag:
    FIELD(arg3, u16, 0x46) &= 0x7FFF;

done:
    return;
}

#undef FIELD

