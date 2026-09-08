#include "common.h"
#include "records/Rec_func_800D6DC0_arg2.h"

typedef struct S_80175594_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    union { u16 s; s16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    s32 unk_AC;
    u8 pad_B0[0x6];
    u16 unk_B6;
} S_80175594_0;   /* arg0 in func_80175594 */

typedef struct S_80175594_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175594_1;   /* arg1 in func_80175594 */


typedef struct S_80175594_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x40];
    s16 unk_88;
} S_80175594_3;   /* object in func_80175594 */



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
    register void *arg2 ASM_REG("$19") = entity_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *object ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 counter;
    s32 attempts;
    s32 random_x4;
    s32 random_x5;
    s16 random_y;
    s16 result;
    s32 dx;
    s32 dy;
    s32 entity_y;
    u8 old_x;
    u8 old_y;
    u8 *world;
    u8 *table;

    ASM_KEEP(arg2);   /* MATCH pin: keeps a statement from moving across a call/branch */

    {
        static void *const sw_keep[] = {
            &&case_0, &&case_1, &&case_2, &&case_3,
            &&case_4, &&case_5, &&case_6, &&case_7
        };
        u32 swi = ((S_80175594_0 *)arg0)->unk_9B;

        if (swi >= 8) {
            goto done;
        }
        object = arg3;
        ASM_KEEP(object);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        (void)sw_keep;
        goto *D_80170920[swi];
    }

case_0:
    ((S_80175594_1 *)arg1)->unk_14 = 0;
    ((S_80175594_1 *)arg1)->unk_10 = 0;
    ((S_80175594_1 *)arg1)->unk_0C = 0;
    if (((Rec_func_800D6DC0_arg2 *)arg2)->unk_14 & 0x8000) {
        ((S_80175594_0 *)arg0)->unk_9B = 7;
        ((Rec_func_800D6DC0_arg2 *)arg2)->unk_14 |= 0x6000;
        goto done;
    }
    if (((S_80175594_0 *)arg0)->unk_A0.at00.v <= 0x6FFFF) {
        goto done;
    }
    ((S_80175594_0 *)arg0)->unk_98 |= 8;
    ((S_80175594_3 *)object)->unk_1C &= ~0x40000;
    ((S_80175594_0 *)arg0)->unk_A0.at00.v = 0;
    ((S_80175594_0 *)arg0)->unk_92.s -= 8;
    ((S_80175594_0 *)arg0)->unk_9B++;
    ((S_80175594_0 *)arg0)->unk_B6 =
        ((S_80175594_1 *)arg1)->unk_0A.s + ((S_80175594_0 *)arg0)->unk_92.s;
    goto done;

case_1:
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E23B8;
    func_80047784(arg2,
        D_800E23B8[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
        0);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    goto next_state;

case_2:
    if (++((S_80175594_0 *)arg0)->unk_96 < 9) {
        goto done;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E23C0;
    func_80047784(arg2,
        D_800E23C0[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
        0);
    goto next_state;

case_3:
    if (((S_80175594_0 *)arg0)->unk_96++ < 3) {
        goto done;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    goto next_state;

case_4:
    if (((S_80175594_0 *)arg0)->unk_96++ < 0xB) {
        goto done;
    }
    counter = 0;
    ((S_80175594_0 *)arg0)->unk_96 = 0;
    ((S_80175594_0 *)arg0)->unk_9B++;
    ((S_80175594_1 *)arg1)->unk_14 = 0;
    ((S_80175594_0 *)arg0)->unk_AC = 0;
    do {
        random_x4 = (s16)(func_8017165C(0x2C) - 0x16);
        random_y = func_8017165C(0x2C) - 0x16;
        func_80171010(arg0, arg1, arg2, random_x4, random_y, 0x1E);
        counter++;
    } while (counter < 6);
    func_800D6DC0(arg0, arg1, arg2, object);
    goto done;

case_5:
    switch (((S_80175594_0 *)arg0)->unk_96) {
    case 0:
        ((S_80175594_1 *)arg1)->unk_14 = -0x140000;
        ((S_80175594_0 *)arg0)->unk_AC = 0x30000;
        break;
    case 6:
        ((S_80175594_1 *)arg1)->unk_14 = -0x180000;
        ((S_80175594_0 *)arg0)->unk_AC = -0x10000;
        break;
    case 12:
        ((S_80175594_0 *)arg0)->unk_AC = -0x20000;
        break;
    }
    ((S_80175594_1 *)arg1)->unk_14 += ((S_80175594_0 *)arg0)->unk_AC;

    if (((S_80175594_0 *)arg0)->unk_96 < 2) {
        counter = 0;
        do {
            random_x5 = (s16)((func_80069EF8() & 0x1F) - 0x10);
            random_y = (func_80069EF8() & 0x1F) - 0x10;
            func_80171010(arg0, arg1, arg2, random_x5, random_y, 0x1E);
            counter++;
        } while (counter < 4);
    }
    if (((S_80175594_0 *)arg0)->unk_96 == 1) {
        func_80170BB8(arg0, arg1, arg2, object, 1);
        func_800A56E0(0x80A);
    }
    if (((S_80175594_0 *)arg0)->unk_96 == 2) {
        func_80170A44(arg0, arg1, arg2, object);
    }
    if (((S_80175594_0 *)arg0)->unk_96 == 6) {
        func_80170BB8(arg0, arg1, arg2, object, 0x1A);
        func_800A56E0(0x705);
    }
    if (((S_80175594_0 *)arg0)->unk_96++ < 0x2E) {
        goto done;
    }
    goto next_state;

case_6:
    ((S_80175594_1 *)arg1)->unk_0A.s = ((S_80175594_0 *)arg0)->unk_B6;

next_state:
    ((S_80175594_0 *)arg0)->unk_96 = 0;
    ((S_80175594_0 *)arg0)->unk_9B++;
    goto done;

case_7:
    func_8009A3D0(((Rec_func_800D6DC0_arg2 *)arg2)->unk_24, ((Rec_func_800D6DC0_arg2 *)arg2)->unk_25,
        (((S_80175594_3 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
    attempts = 0x20;
    world = D_80082E80;
    old_x = ((Rec_func_800D6DC0_arg2 *)arg2)->unk_24;
    old_y = ((Rec_func_800D6DC0_arg2 *)arg2)->unk_25;
    do {
        do {
            result = func_800A4E2C((u8 *)arg2 + 0x24, (u8 *)arg2 + 0x25);
        } while (result < 0);

        dx = world[0x24];
        dy = ((Rec_func_800D6DC0_arg2 *)arg2)->unk_24;
        entity_y = ((Rec_func_800D6DC0_arg2 *)arg2)->unk_25;
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
    ((Rec_func_800D6DC0_arg2 *)arg2)->unk_24 = old_x;
    ((Rec_func_800D6DC0_arg2 *)arg2)->unk_25 = old_y;

coordinates_ready:
    ((S_80175594_1 *)arg1)->unk_02.s = (((Rec_func_800D6DC0_arg2 *)arg2)->unk_24 << 6) + 0x20;
    ((S_80175594_1 *)arg1)->unk_06.s = (((Rec_func_800D6DC0_arg2 *)arg2)->unk_25 << 6) + 0x20;
    result = func_800BCB04(((S_80175594_1 *)arg1)->unk_02.u, ((S_80175594_1 *)arg1)->unk_06.u,
        -0x200);
    result -= 0x11;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    attempts = -0x20;
    ((S_80175594_1 *)arg1)->unk_0A.u = result;
    ((S_80175594_0 *)arg0)->unk_92.u = attempts;
    ((S_80175594_0 *)arg0)->unk_A0.at00.v = 0;
    ((S_80175594_3 *)object)->unk_88 = -0x200;
    result = func_800BCB04(
        (((Rec_func_800D6DC0_arg2 *)arg2)->unk_24 << 6) | 0x20,
        (((Rec_func_800D6DC0_arg2 *)arg2)->unk_25 << 6) | 0x20,
        -0x200);
    ((S_80175594_3 *)object)->unk_88 = result;

    func_8009A21C(((Rec_func_800D6DC0_arg2 *)arg2)->unk_24, ((Rec_func_800D6DC0_arg2 *)arg2)->unk_25,
        (((S_80175594_3 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object);
    func_800AD594(object, 0x1000);
    ((S_80175594_0 *)arg0)->unk_8C = &D_80171F1C;
    D_8008346C = 0;
    ((S_80175594_1 *)arg1)->unk_14 = 0;
    ((S_80175594_1 *)arg1)->unk_10 = 0;
    ((S_80175594_1 *)arg1)->unk_0C = 0;
    ((S_80175594_0 *)arg0)->unk_92.u = attempts;
    ((S_80175594_3 *)object)->unk_1C |= 0x40000;
    (*(u16 *)((u8 *)arg0 + 0x98)) |= 8;

    table = D_800E2348;
    if (((Rec_func_800D6DC0_arg2 *)arg2)->unk_2C != table) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800D6DC0_arg2 *)arg2)->unk_05 = 1;
        ((S_80175594_0 *)arg0)->unk_A0.at02.v = 0;
        ((S_80175594_0 *)arg0)->unk_9E = 0;
    }
    ((S_80175594_3 *)object)->unk_46 &= 0x7FFF;

done:
    return;
}

#undef FIELD
