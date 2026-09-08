#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


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


typedef struct S_801728A8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_801728A8_0;   /* arg0 in func_801728A8 */


typedef struct S_801728A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801728A8_2;   /* call_a0 in func_801728A8 */


typedef struct S_801728A8_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_801728A8_4;   /* arg3 in func_801728A8 */

void func_801728A8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    u8 state;

    state = ((S_801728A8_0 *)arg0)->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    (void)jt_keep;
    goto *D_80170850[state];

L0:
    {
        register void *call_a0 ASM_REG("$4") = arg3;   /* MATCH pin: retail basic-block layout depends on it */

        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
            ((S_801728A8_0 *)arg0)->unk_9B.n = 4;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(call_a0, arg2, ((S_801728A8_2 *)call_a0)->unk_2A, 1);
            return;
        }
    }

L1:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -=
        *(s16 *)((u8 *)&D_8006CCD8 +
                 (((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE)) << 14;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -=
        *(s16 *)((u8 *)&D_8006CCE8 +
                 (((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE)) << 14;
    ((S_801728A8_0 *)arg0)->unk_A0.at00.v += 0x60000;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v >= 0x31) {
        ((S_801728A8_0 *)arg0)->unk_A0.at02.v = 0x30;
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        return;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v < 0x30) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175E58;
    func_80047784(arg2,
        D_80175E58[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_80174910((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A);
    (void)((S_801728A8_0 *)arg0)->unk_9B.v;
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
        register s32 shifted_x ASM_REG("$4");   /* MATCH pin: retail basic-block layout depends on it */
        register s32 shifted_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        s16 timer;

        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(index);   /* MATCH pin: keeps a statement from moving across a call/branch */
        direction_x = *addr_x;
        direction_y = *addr_y;
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 += shifted_x;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v += shifted_y;
        arc = -func_800644B8(((S_801728A8_0 *)arg0)->unk_96.s * 170);
        ((S_801728A8_0 *)arg0)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)arg0)->unk_96.u + 1;
        ((S_801728A8_0 *)arg0)->unk_96.u = timer;
        if (timer < 9) {
            return;
        }
    }
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175E60;
    func_80047784(arg2,
        D_80175E60[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x808);
    ((S_801728A8_0 *)arg0)->unk_9B.n++;
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
        register s32 shifted_x ASM_REG("$4");   /* MATCH pin: retail basic-block layout depends on it */
        register s32 shifted_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        s16 timer;
        s32 velocity_x;
        s32 velocity_y;

        if (((S_801728A8_0 *)arg0)->unk_96.s == 10) {
            func_8009C12C(arg3, arg2, ((S_801728A8_4 *)arg3)->unk_2A.s, 1);
        }
        base_x = (s16 *)&D_8006CCD8;
        base_y = (s16 *)&D_8006CCE8;
        index = ((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE;
        addr_x = (s16 *)(index + (u8 *)base_x);
        addr_y = (s16 *)(index + (u8 *)base_y);
        ASM_KEEP(addr_x);   /* MATCH pin: keeps a constant in a register as retail does */
        direction_x = *addr_x;
        direction_y = *addr_y;
        shifted_x = direction_x << 16;
        shifted_y = direction_y << 16;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 += shifted_x;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v += shifted_y;
        arc = -func_800644B8(((S_801728A8_0 *)arg0)->unk_96.s * 170);
        ((S_801728A8_0 *)arg0)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)arg0)->unk_96.u + 1;
        ((S_801728A8_0 *)arg0)->unk_96.u = timer;
        if (timer < 13) {
            return;
        }
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175E68;
        func_80047784(arg2,
            D_80175E68[((D_80083228 + ((S_801728A8_4 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
            0);

        velocity_x = -*(s16 *)((u8 *)base_x +
            (((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_x += velocity_x >> 2;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = velocity_x;

        velocity_y = -*(s16 *)((u8 *)base_y +
            (((u16)((S_801728A8_4 *)arg3)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_y += velocity_y >> 2;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = velocity_y;
        ((S_801728A8_0 *)arg0)->unk_A8 = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 / 24;
        ((S_801728A8_0 *)arg0)->unk_AC = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v / 24;
    }
    ((S_801728A8_0 *)arg0)->unk_96.s = 12;
    ((S_801728A8_0 *)arg0)->unk_9B.n++;
    return;

L4:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -= ((S_801728A8_0 *)arg0)->unk_A8;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= ((S_801728A8_0 *)arg0)->unk_AC;
    if (((S_801728A8_0 *)arg0)->unk_A0.at02.v > 0) {
        ((S_801728A8_0 *)arg0)->unk_A0.at02u.v -= 0x10;
        func_80172D40();
    }
    ((S_801728A8_0 *)arg0)->unk_A0.at02.v = 0;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_801728A8_0 *)arg0)->unk_8C = &D_801710EC;
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg3 + (0x46))) &= 0x7FFF;
    ((S_801728A8_0 *)arg0)->unk_98 &= 0xFFF7;
    func_800A4ACC(arg3);
}
