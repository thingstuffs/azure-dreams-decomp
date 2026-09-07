#include "common.h"

extern void func_80099FDC(void *);
extern void func_8009FAC4(void);
extern void func_800A48F0(void *, s32, s32);

extern u16 D_80013714[5];
extern u8 *D_800E3D7C[3];
extern u8 *D_80175D50[3];

void func_8016F144(void) {
    s32 i;
    u8 *p;
    void *item;

    i = 0;
    p = D_80175D50[0] + 0x20;
    *(u16 *)(p + 0x46) &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4();
    p[0xAF] = 0;
    p[0xB0] = 1;
    func_800A48F0(p, 7, 1);
    p[0xAE] = 2;
    do {
        item = *(void **)(D_800E3D7C[0] + 0xAC + i * 4);
        if (item != 0) {
            func_80099FDC((u8 *)item - 0x20);
        }
        i++;
    } while (i < 2);
}
