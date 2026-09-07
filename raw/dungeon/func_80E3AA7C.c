#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_8017427C(void *arg0, void *arg1, void *arg2, void *arg3) {
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

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        base = (u8 *)arg0 - 0x20;
        FIELD(arg0, s16, 0x96) = 0x10;
        func_8004491C(base, &D_800C6AEC);
        FIELD(arg2, u32, 0xC) = 0x08000000;
        FIELD(arg2, s16, 0x10) = 0x20;
        FIELD(arg2, u16, 0x12) -= 0x80;
        FIELD(arg2, u16, 0x14) |= 0xC;
        FIELD(arg3, u32, 0x1C) |= 0x40000000;
        FIELD(arg0, u8, 0x9B)++;
        /* fall through */

    case 1:
        timer = FIELD(arg0, s16, 0x96);
        if (timer == 0) {
            goto advance_state;
        }
        fade = FIELD(arg2, u8, 0xC);
        fade += (0x80 - fade) / timer;
        FIELD(arg2, u8, 0xC) = fade;
        FIELD(arg2, u8, 0xE) = fade;
        FIELD(arg2, u8, 0xD) = fade;
        FIELD(arg0, u16, 0x96)--;
        break;

    case 2:
        base = (u8 *)arg0 - 0x20;
        phase = FIELD(arg2, u8, 0xF);
        if (phase >= 2) {
            FIELD(arg2, u8, 0xF) = phase - 1;
            break;
        }
        func_80044A50(base);
        func_8004491C(base, &D_80045340);
        FIELD(arg2, u32, 0xC) = 0x00808080;
        FIELD(arg2, s16, 0x10) = 0;
        FIELD(arg2, u16, 0x12) += 0x80;
        FIELD(arg2, u16, 0x14) &= 0xFFF3;
        func_80174B90(base, (u8 *)arg3 + 0x2A,
                      (u8 *)arg0 + 0x9A, (u8 *)arg0 + 0x98);
advance_state:
        FIELD(arg0, u8, 0x9B)++;
        break;

    case 3:
        FIELD(arg0, u8 *, 0x8C) = D_80170EE4;
        flags = FIELD(arg3, s32, 0x1C);
        FIELD(arg3, s32, 0x1C) = flags & 0xEFFFFFFF;
        if (!(FIELD(arg3, s32, 0x1C) & 0x00400000)) {
            tile_x = FIELD(arg2, u8, 0x24);
            tile_y = FIELD(arg2, u8, 0x25);
            mode = 0x3000;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            func_8009A21C(tile_x, tile_y, mode);
        }
        counter = (u16 *)&D_80083460;
        counter[5]--;
        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(counter, void *, 0x10) = (u8 *)arg3 - 0x20;
            func_800AAA54(arg0, arg1, arg2, D_80176640);
            break;
        }
        if ((FIELD(arg3, s32, 0x14) & 0x4000) &&
            (FIELD(arg3, s32, 0x1C) & 0x10000)) {
            index = (s16)func_800A1BD0(arg3);
            if (index < 0) {
                break;
            }
            func_800956B8(D_800E3D7C, D_80083780, D_80082E80,
                          FIELD(D_800E3D7C + index * 4, s32, 0xD0));
            FIELD(arg3, s32, 0x1C) &= 0xFFFEFFFF;
            break;
        }
        if ((func_80042900(arg3, 0xA) << 0x10) != 0) {
            func_800A48F0(arg3, 0xA, func_80042518(arg3, 0xA));
        }
        break;
    }
}
