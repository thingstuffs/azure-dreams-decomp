#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 D_800814A0;
extern u8 D_80083160[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666B8(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern void func_800A29E4(void);

void func_800A2690(void *arg0)
{
    u16 angle;
    u16 h0;
    u16 x0;
    u16 x1;
    u16 count;
    s16 sx;
    s16 sy;
    s32 center;
    s32 phase;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 d2;
    s32 sum;
    s32 intensity;
    s32 value;
    s32 scaled;
    u8 *source;
    u8 *state;
    u8 *prim;
    u8 *packet;

    source = FIELD(arg0, u8 *, 0x14);
    angle = FIELD(source, u16, 2);
    h0 = FIELD(source, volatile u16, 0);
    x0 = FIELD(source, u16, 4);
    count = FIELD(arg0, u16, 4) - 1;
    x1 = FIELD(source, u16, 6);
    center = h0 + FIELD(arg0, u16, 8) + 0xA0;
    FIELD(arg0, u16, 4) = count;
    sx = x0 + FIELD(arg0, u16, 0xA);
    sy = x1 + FIELD(arg0, u16, 0xC);

    if ((count << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800A29E4();
        return;
    }

    state = *(u8 **)D_80083160;
    prim = FIELD(state, u8 *, 0x8D0);
    FIELD(state, u8 *, 0x8D0) = prim + 0x24;

    phase = func_800644B8(((s16)FIELD(arg0, u16, 4) << 11) /
                         FIELD(arg0, s16, 6));
    intensity = phase / 16;

    a = func_800644B8(sx * 2);
    b = func_800644B8(sx * 4);
    c = func_800644B8(sx * 8);
    d = func_800644B8(sy * 2);
    e = func_800644B8(sy * 4);
    f = func_800644B8(sy * 8);
    sum = a + b + c;
    d2 = d + 0x2400;
    sum += d2;
    sum += e;
    sum += f;
    sum += 0x2400;

    intensity = (intensity * sum) / 36864;
    intensity =
        (intensity * FIELD(FIELD(arg0, u8 *, 0x14), s32, 8)) / 4096;
    intensity /= 4;

    FIELD(prim, s8, 0xE) = intensity;
    FIELD(prim, s8, 0xD) = intensity;
    FIELD(prim, s8, 0xC) = intensity;
    FIELD(prim, s8, 6) = intensity;
    FIELD(prim, s8, 5) = intensity;
    FIELD(prim, s8, 4) = intensity;
    FIELD(prim, s8, 0x16) = 0;
    FIELD(prim, s8, 0x15) = 0;
    FIELD(prim, s8, 0x14) = 0;
    func_800666B8(prim);
    func_80066640(prim, 1);

    FIELD(prim, s16, 8) = center - FIELD(arg0, s32, 0x10) / 32;
    FIELD(prim, s16, 0xA) = 0;
    FIELD(prim, s16, 0x10) = center + FIELD(arg0, s32, 0x10) / 32;
    FIELD(prim, s16, 0x12) = 0;
    FIELD(prim, s16, 0x18) =
        center - (FIELD(arg0, s32, 0x10) * func_800644B8((s16)angle)) / 4096;
    FIELD(prim, s16, 0x1A) =
        (FIELD(arg0, s32, 0x10) * func_80064584((s16)angle)) / 4096;

    state = *(u8 **)D_80083160;
    packet = FIELD(state, u8 *, 0x8D0);
    FIELD(state, u8 *, 0x8D0) = packet + 0xC;
    value = func_80066460(0, 0, 0x140, 0);
    func_80067F20(packet, 0, 0, value & 0xFFFF, 0);
    func_8006658C(*(u8 **)D_80083160 + 0xD8, packet);

    func_8006658C(*(u8 **)D_80083160 + 0xD8, prim);

    state = *(u8 **)D_80083160;
    packet = FIELD(state, u8 *, 0x8D0);
    FIELD(state, u8 *, 0x8D0) = packet + 0xC;
    value = func_80066460(0, 1, 0x140, 0);
    func_80067F20(packet, 0, 0, value & 0xFFFF, 0);
    func_8006658C(*(u8 **)D_80083160 + 0xD8, packet);
}
