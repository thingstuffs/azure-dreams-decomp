#include "common.h"

typedef struct S_8017427C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017427C_0;   /* arg0 in func_8017427C */

typedef struct S_8017427C_1 {
    u8 pad_00[0xC];
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017427C_1;   /* arg2 in func_8017427C */

typedef struct S_8017427C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x8];
    u8 unk_28;
} S_8017427C_2;   /* arg3 in func_8017427C */

typedef struct S_8017427C_3 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8017427C_3;   /* counter in func_8017427C */

typedef struct S_8017427C_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8017427C_4;   /* D_800E3D7C + index * 4 in func_8017427C */



extern s8 func_80042518(void *, s32);
extern s32 func_80042900(void *, s32);
extern void func_8004491C(void *, void *);
extern void func_80044A50(void *);
extern void func_800956B8(void *, void *, void *, s32);
extern void func_8009A21C(u8, u8, s32);
extern s32 func_800A1BD0(void *);
extern void func_800A48F0(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_80174B90(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern s32 D_800C6AEC;
extern u8 *D_800E3D7C;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

void func_8017427C(void *arg0, void *arg1, S_8017427C_1 *arg2, void *arg3) {
    void *base;
    s32 flags;
    s32 index;
    s32 mode;
    u8 fade;
    u8 phase;
    u8 state;
    u8 tile_x;
    u8 tile_y;
    s16 timer;
    u16 *counter;

    state = ((S_8017427C_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        base = (u8 *)arg0 - 0x20;
        ((S_8017427C_0 *)arg0)->unk_96.s = 0x10;
        func_8004491C(base, &D_800C6AEC);
        arg2->unk_0C.at00.v = 0x08000000;
        arg2->unk_10 = 0x20;
        arg2->unk_12 -= 0x80;
        arg2->unk_14 |= 0xC;
        ((S_8017427C_2 *)arg3)->unk_1C.u |= 0x40000000;
        ((S_8017427C_0 *)arg0)->unk_9B++;
        /* fall through */

    case 1:
        timer = ((S_8017427C_0 *)arg0)->unk_96.s;
        if (timer == 0) {
            goto advance_state;
        }
        fade = arg2->unk_0C.at00u.v;
        fade += (0x80 - fade) / timer;
        arg2->unk_0C.at00u.v = fade;
        arg2->unk_0C.at02.v = fade;
        arg2->unk_0C.at01.v = fade;
        ((S_8017427C_0 *)arg0)->unk_96.u--;
        break;

    case 2:
        base = (u8 *)arg0 - 0x20;
        phase = arg2->unk_0C.at03.v;
        if (phase >= 2) {
            arg2->unk_0C.at03.v = phase - 1;
            break;
        }
        func_80044A50(base);
        func_8004491C(base, &D_80045340);
        arg2->unk_0C.at00.v = 0x00808080;
        arg2->unk_10 = 0;
        arg2->unk_12 += 0x80;
        arg2->unk_14 &= 0xFFF3;
        func_80174B90(base, (u8 *)arg3 + 0x2A,
                      (u8 *)arg0 + 0x9A, (u8 *)arg0 + 0x98);
advance_state:
        ((S_8017427C_0 *)arg0)->unk_9B++;
        break;

    case 3:
        ((S_8017427C_0 *)arg0)->unk_8C = D_80170EE4;
        flags = ((S_8017427C_2 *)arg3)->unk_1C.s;
        ((S_8017427C_2 *)arg3)->unk_1C.s = flags & 0xEFFFFFFF;
        if (!(((S_8017427C_2 *)arg3)->unk_1C.s & 0x00400000)) {
            tile_x = arg2->unk_24;
            tile_y = arg2->unk_25;
            mode = 0x3000;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            func_8009A21C(tile_x, tile_y, mode);
        }
        counter = (u16 *)&D_80083460;
        counter[5]--;
        if (((S_8017427C_2 *)arg3)->unk_28 == 0) {
            ((S_8017427C_3 *)counter)->unk_10 = (u8 *)arg3 - 0x20;
            func_800AAA54(arg0, arg1, arg2, D_80176640);
            break;
        }
        if ((((S_8017427C_2 *)arg3)->unk_14 & 0x4000) &&
            (((S_8017427C_2 *)arg3)->unk_1C.s & 0x10000)) {
            index = (s16)func_800A1BD0(arg3);
            if (index < 0) {
                break;
            }
            func_800956B8(D_800E3D7C, D_80083780, D_80082E80,
                          ((S_8017427C_4 *)(D_800E3D7C + index * 4))->unk_D0);
            ((S_8017427C_2 *)arg3)->unk_1C.s &= 0xFFFEFFFF;
            break;
        }
        if ((func_80042900(arg3, 0xA) << 0x10) != 0) {
            func_800A48F0(arg3, 0xA, func_80042518(arg3, 0xA));
        }
        break;
    }
}
