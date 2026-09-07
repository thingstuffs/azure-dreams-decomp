#include "common.h"

extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, s32, s32, s32);
extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);

extern s16 D_80083228[];
extern u16 D_80083462[];
extern u8 D_80175F30[];

s32 func_801723D8(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *a = arg0;
    u8 *b = arg2;
    u8 *c = arg3;

    c[0x71] &= 0x7F;
    if (!(D_80083462[0] & 0x2000)) {
        if ((*(u16 *)(c + 0x46) & 0x8000) || !(D_80083462[0] & 8)) {
            if ((func_800A2B5C(c) << 16) == 0) {
                func_800C7930(c - 0x20, arg1, 8, 0x300);
                if ((func_800A2B5C(c) << 16) == 0) {
                    a[0x9A] = 0x18;
                    a[0x9B] = 0;
                    *(s32 *)(a + 0x8C) = 0;
                    *(u8 **)(b + 0x2C) = D_80175F30;
                    func_80047784(b, D_80175F30[((D_80083228[0] + *(s16 *)(c + 0x2A) + 0x100) >> 9) & 7], 0);
                    func_800A4ACC(c);
                    c[0x6D]--;
                    return 0;
                }
            }
        }
    }
    return -1;
}
