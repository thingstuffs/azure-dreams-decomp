#include "common.h"

extern s32 D_80174CD8[3];
extern s32 D_800E296C[3];
extern u16 D_80013714[5];
extern u8 *D_800E3D7C[3];

extern void func_8009FAC4(void);
extern void func_80173ED0(void);
extern void func_80099FDC(void *);

void func_8017105C(void) {
    s32 i;
    void *object;
    u8 *ptr;
    u16 *h = D_80013714;

    ptr = (u8 *)(D_80174CD8[0] + 0x20);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    D_800E296C[0] &= 0xF7FFFFFF;
    h[0] &= 0xFFF6;
    func_8009FAC4();
    func_80173ED0();

    i = 0;
    do {
        object = *(void **)(D_800E3D7C[0] + 0xAC + i * 4);
        if (object != 0) {
            func_80099FDC((u8 *)object - 0x20);
        }
        i++;
    } while (i < 2);
}
