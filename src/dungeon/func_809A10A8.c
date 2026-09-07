#include "common.h"

typedef struct S_801728A8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 s; volatile u8 u; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_801728A8_0;   /* arg0 in func_801728A8 */

typedef struct S_801728A8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801728A8_1;   /* arg2 in func_801728A8 */

typedef struct S_801728A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801728A8_2;   /* call_a0 in func_801728A8 */

typedef struct S_801728A8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801728A8_3;   /* arg1 in func_801728A8 */

typedef struct S_801728A8_4 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
} S_801728A8_4;   /* arg3 in func_801728A8 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80172B38(void) __attribute__((noreturn));
extern void func_80172D40(void) __attribute__((noreturn));
extern void func_80174910(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170850[];
extern s32 D_801710EC;
extern u8 D_80175E58[];
extern u8 D_80175E60[];
extern u8 D_80175E68[];

void func_801728A8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    u8 state;

    state = ((S_801728A8_0 *)arg0)->unk_9B.s;
    if ((u32)state >= 5) {
        return;
    }
    (void)jt_keep;
    goto *D_80170850[state];

L0:
    {
        void *call_a0 = arg3;

        if (((S_801728A8_1 *)arg2)->unk_14 & 0x8000) {
            ((S_801728A8_0 *)arg0)->unk_9B.s = 4;
            ((S_801728A8_1 *)arg2)->unk_14 |= 0x6000;
            func_8009C12C(call_a0, arg2, ((S_801728A8_2 *)call_a0)->unk_2A, 1);
            return;
        }
    }

L1:
    ((S_801728A8_3 *)arg1)->unk_0C -=
        *(s16 *)((u8 *)&D_8006CCD8 +
                 (((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE)) << 14;
    ((S_801728A8_3 *)arg1)->unk_10 -=
        *(s16 *)((u8 *)&D_8006CCE8 +
                 (((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE)) << 14;
    ((S_801728A8_0 *)arg0)->unk_A0.at00.v += 0x60000;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v >= 0x31) {
        ((S_801728A8_0 *)arg0)->unk_A0.at02.v = 0x30;
    }
    if (!(((S_801728A8_1 *)arg2)->unk_14 & 0x6000)) {
        return;
    }
    ((S_801728A8_3 *)arg1)->unk_14 = 0;
    ((S_801728A8_3 *)arg1)->unk_10 = 0;
    ((S_801728A8_3 *)arg1)->unk_0C = 0;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v < 0x30) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175E58;
    func_80047784(arg2,
        D_80175E58[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    func_80174910((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A);
    (void)((S_801728A8_0 *)arg0)->unk_9B.u;
    ((S_801728A8_0 *)arg0)->unk_96.s = 0;
    func_80172B38();

L2:
    {
        s16 *base_x;
        s16 *base_y;
        s16 *addr_x;
        register s16 *addr_y ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 arc;
        register s32 index ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 direction_x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 direction_y ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 shifted_x ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 shifted_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        s16 timer;

        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(index);   /* MATCH pin: keeps a statement from moving across a call/branch */
        direction_x = *addr_x;
        direction_y = *addr_y;
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ((S_801728A8_3 *)arg1)->unk_0C += shifted_x;
        ((S_801728A8_3 *)arg1)->unk_10 += shifted_y;
        arc = -func_800644B8(((S_801728A8_0 *)arg0)->unk_96.s * 170);
        ((S_801728A8_0 *)arg0)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)arg0)->unk_96.u + 1;
        ((S_801728A8_0 *)arg0)->unk_96.u = timer;
        if (timer < 9) {
            return;
        }
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175E60;
    func_80047784(arg2,
        D_80175E60[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x808);
    ((S_801728A8_0 *)arg0)->unk_9B.s++;
    return;

L3:
    {
        s16 *base_x;
        s16 *base_y;
        s16 *addr_x;
        s16 *addr_y;
        s32 arc;
        register s32 direction_x ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 direction_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 index;
        register s32 shifted_x ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 shifted_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        s16 timer;
        s32 velocity_x;
        s32 velocity_y;

        if (((S_801728A8_0 *)arg0)->unk_96.s == 10) {
            func_8009C12C(arg3, arg2, ((S_801728A8_4 *)arg3)->unk_2A.u, 1);
        }
        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(addr_x);   /* MATCH pin: keeps a constant in a register as retail does */
        direction_x = *addr_x;
        direction_y = *addr_y;
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ((S_801728A8_3 *)arg1)->unk_0C += shifted_x;
        ((S_801728A8_3 *)arg1)->unk_10 += shifted_y;
        arc = -func_800644B8(((S_801728A8_0 *)arg0)->unk_96.s * 170);
        ((S_801728A8_0 *)arg0)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)arg0)->unk_96.u + 1;
        ((S_801728A8_0 *)arg0)->unk_96.u = timer;
        if (timer < 13) {
            return;
        }
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175E68;
        func_80047784(arg2,
            D_80175E68[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
            0);

        velocity_x = -*(s16 *)((u8 *)base_x +
            (((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE)) << 18;
        velocity_x += velocity_x >> 2;
        ((S_801728A8_3 *)arg1)->unk_0C = velocity_x;

        velocity_y = -*(s16 *)((u8 *)base_y +
            (((u16)((S_801728A8_4 *)arg3)->unk_2A.s >> 8) & 0xE)) << 18;
        velocity_y += velocity_y >> 2;
        ((S_801728A8_3 *)arg1)->unk_10 = velocity_y;
        ((S_801728A8_0 *)arg0)->unk_A8 = ((S_801728A8_3 *)arg1)->unk_0C / 24;
        ((S_801728A8_0 *)arg0)->unk_AC = ((S_801728A8_3 *)arg1)->unk_10 / 24;
    }
    ((S_801728A8_0 *)arg0)->unk_96.s = 12;
    ((S_801728A8_0 *)arg0)->unk_9B.s++;
    return;

L4:
    ((S_801728A8_3 *)arg1)->unk_0C -= ((S_801728A8_0 *)arg0)->unk_A8;
    ((S_801728A8_3 *)arg1)->unk_10 -= ((S_801728A8_0 *)arg0)->unk_AC;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v > 0) {
        ((S_801728A8_0 *)arg0)->unk_A0.at02u.v -= 0x10;
        func_80172D40();
    }
    ((S_801728A8_0 *)arg0)->unk_A0.at02.v = 0;
    if (!(((S_801728A8_1 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    ((S_801728A8_3 *)arg1)->unk_14 = 0;
    ((S_801728A8_3 *)arg1)->unk_10 = 0;
    ((S_801728A8_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801728A8_1 *)arg2)->unk_24, ((S_801728A8_1 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_801728A8_0 *)arg0)->unk_8C = &D_801710EC;
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    ((S_801728A8_0 *)arg0)->unk_98 &= 0xFFF7;
    func_800A4ACC(arg3);
}
