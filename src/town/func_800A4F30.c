#include "common.h"

typedef struct S_800A2690_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    u8 * unk_14;
} S_800A2690_0;   /* arg0 in func_800A2690 */

typedef struct S_800A2690_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800A2690_1;   /* source in func_800A2690 */

typedef struct S_800A2690_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2690_2;   /* state in func_800A2690 */

typedef struct S_800A2690_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s16 unk_08;
    s16 unk_0A;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    s8 unk_14;
    s8 unk_15;
    s8 unk_16;
    u8 pad_17[0x1];
    s16 unk_18;
} S_800A2690_3;   /* prim in func_800A2690 */

typedef struct S_800A2690_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A2690_4;   /* ((S_800A2690_0 *)arg0)->unk_14 in func_800A2690 */



extern s32 D_800814A0;
extern u8 D_80083160[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666B8(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

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

    source = ((S_800A2690_0 *)arg0)->unk_14;
    angle = ((S_800A2690_1 *)source)->unk_02;
    h0 = ((S_800A2690_1 *)source)->unk_00;
    x0 = ((S_800A2690_1 *)source)->unk_04;
    count = ((S_800A2690_0 *)arg0)->unk_04 - 1;
    x1 = ((S_800A2690_1 *)source)->unk_06;
    center = h0 + ((S_800A2690_0 *)arg0)->unk_08 + 0xA0;
    ((S_800A2690_0 *)arg0)->unk_04 = count;
    sx = x0 + ((S_800A2690_0 *)arg0)->unk_0A;
    sy = x1 + ((S_800A2690_0 *)arg0)->unk_0C;

    if ((count << 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    } else {
        state = *(u8 **)D_80083160;
        prim = ((S_800A2690_2 *)state)->unk_8D0;
        ((S_800A2690_2 *)state)->unk_8D0 = prim + 0x24;

        phase = func_800644B8(((s16)((S_800A2690_0 *)arg0)->unk_04 << 11) /
                             ((S_800A2690_0 *)arg0)->unk_06);
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
            (intensity * ((S_800A2690_4 *)(((S_800A2690_0 *)arg0)->unk_14))->unk_08) / 4096;
        intensity /= 4;

        ((S_800A2690_3 *)prim)->unk_0E = intensity;
        ((S_800A2690_3 *)prim)->unk_0D = intensity;
        ((S_800A2690_3 *)prim)->unk_0C = intensity;
        ((S_800A2690_3 *)prim)->unk_06 = intensity;
        ((S_800A2690_3 *)prim)->unk_05 = intensity;
        ((S_800A2690_3 *)prim)->unk_04 = intensity;
        ((S_800A2690_3 *)prim)->unk_16 = 0;
        ((S_800A2690_3 *)prim)->unk_15 = 0;
        ((S_800A2690_3 *)prim)->unk_14 = 0;
        func_800666B8(prim);
        func_80066640(prim, 1);

        ((S_800A2690_3 *)prim)->unk_08 = center - ((S_800A2690_0 *)arg0)->unk_10 / 32;
        ((S_800A2690_3 *)prim)->unk_0A = 0;
        ((S_800A2690_3 *)prim)->unk_10 = center + ((S_800A2690_0 *)arg0)->unk_10 / 32;
        ((S_800A2690_3 *)prim)->unk_12 = 0;
        ((S_800A2690_3 *)prim)->unk_18 =
            center - (((S_800A2690_0 *)arg0)->unk_10 * func_800644B8((s16)angle)) / 4096;
        (*(s16 *)((u8 *)prim + 0x1A)) =
            (((S_800A2690_0 *)arg0)->unk_10 * func_80064584((s16)angle)) / 4096;

        state = *(u8 **)D_80083160;
        packet = ((S_800A2690_2 *)state)->unk_8D0;
        ((S_800A2690_2 *)state)->unk_8D0 = packet + 0xC;
        value = func_80066460(0, 0, 0x140, 0);
        func_80067F20(packet, 0, 0, value & 0xFFFF, 0);
        func_8006658C(*(u8 **)D_80083160 + 0xD8, packet);

        func_8006658C(*(u8 **)D_80083160 + 0xD8, prim);

        state = *(u8 **)D_80083160;
        packet = ((S_800A2690_2 *)state)->unk_8D0;
        ((S_800A2690_2 *)state)->unk_8D0 = packet + 0xC;
        value = func_80066460(0, 1, 0x140, 0);
        func_80067F20(packet, 0, 0, value & 0xFFFF, 0);
        func_8006658C(*(u8 **)D_80083160 + 0xD8, packet);
    }
}
