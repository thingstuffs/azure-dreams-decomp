#include "common.h"

extern s32 func_80098864();
extern s32 func_8008D344();
extern s32 func_800A6480();
extern s32 func_800AD6FC();
extern s32 func_800A5F38();
extern s32 func_8009BF7C();
extern s32 func_800A56E0();
extern s32 func_8009D6F4();
extern s32 func_800403BC();
extern s32 func_800997FC();
extern s32 func_80098B38();

extern s32 D_80083160[];
extern void *D_800E3D7C;
extern s32 D_800E296C;
extern u8 D_800DDE84[];
extern u16 D_80083460[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern u8 D_800E3648[];
extern u8 D_800E39C8[];
extern u8 D_800E1863;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u8 D_800CE028[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

s32 func_800C3D3C(void *arg0, s32 arg1, s16 arg2, s32 arg3) {
    s32 *b160 = D_80083160;
    u8 *info;
    s32 grid;
    void *ent;
    void *ent0;
    u8 *p1;
    u8 *p0;
    register s32 i ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 x;
    s32 y;
    s32 idx;
    s32 c68;
    register s32 mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 av1 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 se;
    u16 *cell;

    av1 = arg1;
    info = (u8 *) (b160 + 119);
    grid = b160[119];
    se = arg2;
    ASM_KEEP_NV(av1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (se == 13) {
        return func_80098864(av1, arg3);
    }
    if (arg0 == D_800E3D7C) {
        S32(arg0, 0x110) = av1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, av1, se);
        if (func_800AD6FC(arg0, U16(D_800DDE84, U8(arg0, 0x13) * 2) & 3, av1) == 0) {
            func_800A5F38(arg0, av1);
            return 1;
        }
        D_80083460[5] = D_80083460[5] - 1;
        func_80098B38(av1);
        return 1;
    }
    if (D_800E296C & 0x20000000) {
        func_8009BF7C(1, 8, se);
        func_800A56E0(0x80F);
        ent = D_800E3D7C;
        ent0 = ent;
        do {
            S16(ent, 0x88) = 0;
            S32(ent, 0x1C) = S32(ent, 0x1C) | 0x40000000;
            ent = (void *) (S32(ent, 0x5C) + 0x20);
        } while (ent != ent0);
        i = 0;
        p1 = D_800E36C8;
        p0 = D_800E3548;
        do {
            if (U8(p0, 1) != 0) {
                S16(p1, 4) = 0;
            }
            p1 += 0xC;
            i += 1;
            p0 += 4;
        } while (i < 0x40);
        i = 0;
        p1 = D_800E39C8;
        p0 = D_800E3648;
        do {
            if (U8(p0, 1) != 0) {
                S16(p1, 0x12) = 0;
            }
            p1 += 0x18;
            i += 1;
            p0 += 4;
        } while (i < 0x20);
        y = 1;
        c68 = 0x68;
        do {
            x = 1;
            do {
                cell = (u16 *) ((x + (y << S16(info, 0x14))) * 6 + grid);
                if (*cell >= 0xBU) {
                    *cell = c68;
                    cell = (u16 *) ((x + (y << S16(info, 0x14))) * 6 + grid);
                    U16(cell, 4) = U16(cell, 4) & 0x7B32;
                }
                idx = x + (y << S16(info, 0x14));
                x += 1;
                U16((u16 *) (idx * 6 + grid), 2) = 0;
            } while (x < 0x3F);
            y += 1;
        } while (y < 0x3F);
        func_8009D6F4();
        mask = 0x3FF7FFFF;
        D_800E296C = D_800E296C & mask;
        func_800403BC(D_800CE028, mask);
    } else {
        func_800997FC(&D_800E1863, arg3, se);
    }
    D_80083460[5] = D_80083460[5] - 1;
    func_80098B38(av1);
    return 1;
}
