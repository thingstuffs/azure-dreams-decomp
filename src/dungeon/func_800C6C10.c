#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern s16 D_8006CCD8[], D_8006CCE8[];
extern s32 func_8009B390();
extern void func_8009CE1C();
extern s16 func_800B500C();
extern s16 func_800A70E4();
extern void func_800CCC20();
extern u8 D_800E3648[], D_800E3548[];
extern u8 *D_800E3D7C[];
extern u32 D_800814A0[3];

void func_800CC370(void *p)
{
    s32 x;
    s16 i;

    U16(p, 0) += D_8006CCD8[U8(p, 6)];
    U16(p, 2) += D_8006CCE8[U8(p, 6)];
    x = func_8009B390(U16(p, 0), U16(p, 2), S16(p, 4));
    if (x) {
        func_8009CE1C(x, 6, U8(D_800E3D7C[0], 0x11), 9,
                      (s16)(U8(p, 6) << 9), 0, 3);
    }
    i = func_800B500C(S16(p, 0), S16(p, 2), S16(p, 4));
    if (i >= 0) {
        if (D_800E3648[i * 4] == 7) {
            func_800CCC20(0, i);
        } else {
            U32(D_800E3648, i * 4) = 0;
        }
    }
    i = func_800A70E4(S16(p, 0), S16(p, 2), S16(p, 4));
    if (i >= 0) {
        U32(D_800E3548, i * 4) = 0;
    }
    U8(p, 7)--;
    if (!U8(p, 7)) {
        U16(p, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
