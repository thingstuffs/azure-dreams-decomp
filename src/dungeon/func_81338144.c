#include "common.h"

extern void func_80099FDC(void *);
extern void func_8009FAC4(s32, s32, s32, s32);
extern void func_800A48F0(void *, s32, s32);

extern u16 D_80013714[5];
extern u8 *D_800E3D7C[3];
extern u8 *D_80175D50[3];

void func_8016F144(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    u8 *p;
    void *item;
    /* MATCH: keep the byte-store constant in v0, independent of outgoing a2. */
    register s32 one ASM_REG("$2");
    /* MATCH: prepare outgoing a0 before materializing the byte-store constant. */
    register u8 *callp ASM_REG("$4");

    i = 0;
    p = D_80175D50[0] + 0x20;
    *(u16 *)(p + 0x46) &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4(arg0, arg1, arg2, arg3);
    callp = p;
    ASM_KEEP_NV(callp);
    one = 1;
    ASM_KEEP_NV(one);
    p[0xAF] = 0;
    p[0xB0] = one;
    func_800A48F0(callp, 7, 1);
    p[0xAE] = 2;
    do {
        item = *(void **)(D_800E3D7C[0] + 0xAC + i * 4);
        if (item != 0) {
            func_80099FDC((u8 *)item - 0x20);
        }
        i++;
    } while (i < 2);
}
