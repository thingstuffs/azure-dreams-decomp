#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80175CD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0x10];
    union { s16 s; u16 u; } unk_B4;   /* accessed as both */
} S_80175CD8_0;   /* arg0 in func_80175CD8 */



typedef struct S_80175CD8_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175CD8_3;   /* arg1 in func_80175CD8 */

typedef struct S_80175CD8_4 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_80175CD8_4;   /* held in func_80175CD8 */

typedef struct S_80175CD8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x68];
    union { u16 s; s16 u; } unk_88;   /* accessed as both */
} S_80175CD8_5;   /* globals in func_80175CD8 */

typedef struct S_80175CD8_6 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x7A];
    s16 unk_92;
} S_80175CD8_6;   /* global_ptr in func_80175CD8 */



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
        u32 state = ((S_80175CD8_0 *)arg0)->unk_9B;

        if (state >= 0x15) {
            goto done;
        }
        (void)sw_keep;
        goto *D_801709F0[state];
    }

state_0:
    {
        register u8 *pin_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
        s32 pin_a1;
        register s32 dx ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 dy;
        u8 w24;
        u8 c24;
        u8 c25;
        u8 w25;

        pin_a0 = arg3;
        world0 = D_80082E80;
        ASM_KEEP(world0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        pin_a1 = 0x2000;
        ASM_KEEP(pin_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
        w24 = world0[0x24];
        c24 = ((Rec_D_80082E80 *)arg2)->unk_24;
        c25 = ((Rec_D_80082E80 *)arg2)->unk_25;
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
        ((S_80175CD8_0 *)arg0)->unk_96.s = ((dx + dy) * 4) + 9;
        ((S_80175CD8_0 *)arg0)->unk_9B++;
        func_800AD594(pin_a0, pin_a1);
    }

    if (world0[0x24] == ((Rec_D_80082E80 *)arg2)->unk_24) {
        if (world0[0x25] > ((Rec_D_80082E80 *)arg2)->unk_25) {
            direction = 2;
        } else {
            direction = 6;
        }
    } else if (world0[0x25] == ((Rec_D_80082E80 *)arg2)->unk_25) {
        direction = (((Rec_D_80082E80 *)arg2)->unk_24 >= world0[0x24]) * 4;
    } else if (((Rec_D_80082E80 *)arg2)->unk_24 < world0[0x24]) {
        if (((Rec_D_80082E80 *)arg2)->unk_25 < world0[0x25]) {
            direction = 1;
        } else {
            direction = 7;
        }
    } else if (((Rec_D_80082E80 *)arg2)->unk_25 < world0[0x25]) {
        direction = 3;
    } else {
        direction = 5;
    }
    (*(s16 *)((u8 *)arg3 + 0x2A)) = direction << 9;

    if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_10.at01_u8.v >= D_8008146C) {
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
    timer1 = ((S_80175CD8_0 *)arg0)->unk_96.s;
    if (timer1 >= 0xE) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer1 - 9);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 9);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 9);
    } else if (timer1 >= 0xB) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer1 - 7);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 7);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 7);
    } else if (timer1 >= 5) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer1 - 2);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 2);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 2);
    } else {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / timer1;
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            ((S_80175CD8_0 *)arg0)->unk_96.s;
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            ((S_80175CD8_0 *)arg0)->unk_96.s;
    }
    goto decrement_timer;

state_2:
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2368;
    value = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, D_800E2368[value & 7], 0);
    ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
    ((S_80175CD8_0 *)arg0)->unk_9B++;
    func_80094E34();
    goto done;

state_3:
    {
        u16 old_timer = ((S_80175CD8_0 *)arg0)->unk_96.u;

        ((S_80175CD8_0 *)arg0)->unk_96.s = old_timer + 1;
        if ((s16)old_timer < 7) {
            goto done;
        }
    }
    ((S_80175CD8_0 *)arg0)->unk_9B++;
    {
        u8 *held = D_800E3D7C;

        ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
        ((S_80175CD8_4 *)held)->unk_14 |= 0x100000;
    }
    func_800A56E0(0x603);
    goto done;

state_4:
    {
        u8 *globals = D_80083780;
        s32 accel = (s32)0xFFF40000;

        ((S_80175CD8_3 *)arg1)->unk_14 = accel;
        ((S_80175CD8_5 *)globals)->unk_08 += accel;
    }
    {
        u16 old_timer = ((S_80175CD8_0 *)arg0)->unk_96.u;

        ((S_80175CD8_0 *)arg0)->unk_96.s = old_timer + 1;
        if ((s16)old_timer < 0x1B) {
            goto done;
        }
    }
    ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
    ASM_KEEP(arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    if ((D_80012090 == 0) && (D_8008146C == 0x28)) {
        ((S_80175CD8_0 *)arg0)->unk_9B = 7;
    } else if (((Rec_D_800E3D7C *)arg3)->unk_10.at01_u8.v >= D_8008146C) {
        ((S_80175CD8_0 *)arg0)->unk_9B++;
    } else {
        ((S_80175CD8_0 *)arg0)->unk_9B = 7;
    }
    goto done;

state_5:
    ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
    ((S_80175CD8_0 *)arg0)->unk_9B++;
    goto done;

state_6:
    func_800945E8(D_800E3D7C);
    func_800948BC();
    func_800A6780();
    {
        u8 *page8;
        u8 *page_1;
        s16 *counts;
        register u8 call_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */
        s32 count32;
        register u16 count16 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

        page8 = (u8 *)0x80080000;
        ASM_KEEP(page8);   /* MATCH pin: retail schedule: same instructions, different order without it */
        page_1 = (u8 *)0x80010000;
        ASM_KEEP(page_1);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    ((S_80175CD8_3 *)arg1)->unk_14 = 0;
    ((S_80175CD8_3 *)arg1)->unk_10 = 0;
    ((S_80175CD8_3 *)arg1)->unk_0C = 0;
    ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
    ((S_80175CD8_0 *)arg0)->unk_9B = 0x14;
    goto clear_object_flag;

state_7:
    {
        u8 *global_ptr = D_800E3D7C;
        u8 *globals;
        u32 masked;
        u16 height;

        masked = ((S_80175CD8_6 *)global_ptr)->unk_14 & 0xFFEFFFFF;
        ASM_KEEP(masked);   /* MATCH pin: keeps a statement from moving across a call/branch */
        globals = D_80083498;
        globals += 0x20;
        ((S_80175CD8_6 *)global_ptr)->unk_14 = masked;
        height = D_8008378A - ((S_80175CD8_5 *)globals)->unk_88.s;
        ((S_80175CD8_6 *)global_ptr)->unk_92 = height;
        ((S_80175CD8_5 *)globals)->unk_88.u = height;
        ((S_80175CD8_5 *)globals)->unk_1C |= 0x40000000;
    }
    (*(s16 *)((u8 *)arg0 + 0x96)) = 0x28;
    ((S_80175CD8_0 *)arg0)->unk_9B++;

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
    target_x = ((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 16;
    target_y = ((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 16;
    target_z = (((S_80175CD8_0 *)arg0)->unk_B4.s - 0x20) << 16;
    timer8 = ((S_80175CD8_0 *)arg0)->unk_96.s;
    if (timer8 >= 0xE) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer8 - 9);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 9);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 9);
    } else if (timer8 >= 0xB) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer8 - 7);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 7);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 7);
    } else if (timer8 >= 5) {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / (timer8 - 2);
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 2);
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            (((S_80175CD8_0 *)arg0)->unk_96.s - 2);
    } else {
        ((S_80175CD8_3 *)arg1)->unk_0C = (target_x - ((S_80175CD8_3 *)arg1)->unk_00.at00.v) / timer8;
        ((S_80175CD8_3 *)arg1)->unk_10 = (target_y - ((S_80175CD8_3 *)arg1)->unk_04.at00.v) /
            ((S_80175CD8_0 *)arg0)->unk_96.s;
        ((S_80175CD8_3 *)arg1)->unk_14 = (target_z - ((S_80175CD8_0 *)arg0)->unk_90.at00.v) /
            ((S_80175CD8_0 *)arg0)->unk_96.s;
    }

decrement_timer:
    value = ((S_80175CD8_0 *)arg0)->unk_96.u - 1;
    ((S_80175CD8_0 *)arg0)->unk_96.s = value;
    if ((value << 16) != 0) {
        goto done;
    }
    ((S_80175CD8_0 *)arg0)->unk_96.s = 0;
    ((S_80175CD8_0 *)arg0)->unk_9B++;
    ((S_80175CD8_3 *)arg1)->unk_14 = 0;
    ((S_80175CD8_3 *)arg1)->unk_10 = 0;
    ((S_80175CD8_3 *)arg1)->unk_0C = 0;
    goto done;

state_9:
    ((S_80175CD8_3 *)arg1)->unk_14 = 0;
    ((S_80175CD8_3 *)arg1)->unk_10 = 0;
    ((S_80175CD8_3 *)arg1)->unk_0C = 0;
    ((S_80175CD8_0 *)arg0)->unk_8C = &D_80171F1C;
    ((S_80175CD8_0 *)arg0)->unk_9A = 0xE;
    D_8008346C = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
    (*(u16 *)((u8 *)arg0 + 0x98)) &= 0xFFF7;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2348;
    value = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, D_800E2348[value & 7], 0);
    ((Rec_D_80082E80 *)arg2)->unk_05.as_u8 = 1;
    ((S_80175CD8_0 *)arg0)->unk_A2.s = 0;
    ((S_80175CD8_0 *)arg0)->unk_9E = 0;
    ((S_80175CD8_0 *)arg0)->unk_90.at02.v = -0x20;
    ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 = ((S_80175CD8_0 *)arg0)->unk_B4.u;
    ((S_80175CD8_3 *)arg1)->unk_00.at02.v = (((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20;
    ((S_80175CD8_3 *)arg1)->unk_04.at02.v = (((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20;
    ((S_80175CD8_3 *)arg1)->unk_0A = ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 +
        ((S_80175CD8_0 *)arg0)->unk_90.at02u.v - ((S_80175CD8_0 *)arg0)->unk_A2.u;

clear_object_flag:
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;

done:
    return;
}

#undef FIELD

