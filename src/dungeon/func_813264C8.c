#include "common.h"

extern void func_8016AC30();
extern void func_8009FAC4();
extern void func_80047784();
extern void func_80099FDC();

extern u8 *D_80174704;
extern u8 D_80174684[];
extern u16 D_80013714;
extern s16 D_80083228;
extern u8 *D_800E3D7C;

void func_8016DCC8(void)
{
    s32 i;
    s32 object;
    u8 *base;
    u8 *linked;

    func_8016AC30();
    base = D_80174704 + 0x20;
    linked = *(u8 **)(D_80174704 + 0xC);
    *(u16 *)(base + 0x46) &= 0x7FFF;
    D_80013714 &= 0xFFF6;
    func_8009FAC4();
    base[0xB3] = 1;
    base[0xB2] = 0;
    if (*(u8 **)(linked + 0x2C) != D_80174684) {
        *(u8 **)(linked + 0x2C) = D_80174684;
        func_80047784(linked,
            D_80174684[((D_80083228 + *(s16 *)(base + 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    i = 0;
    do {
        object = *(s32 *)(D_800E3D7C + (i * 4) + 0xAC);
        if (object != 0) {
            func_80099FDC(object - 0x20);
        }
        i++;
    } while (i < 2);
}
