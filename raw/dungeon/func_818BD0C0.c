#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800249AC(void) __attribute__((noreturn));
extern void func_8003DB94();
extern void func_800478B8();
extern u8 D_80025E04[];
extern s32 D_800814A0[3];

void func_818BD0C0(void *arg0, s32 arg1, void *arg2)
{
    void *p;
    u16 n;

    p = FIELD(arg0, void *, 0);
    FIELD(p, u16, 0x14)++;
    FIELD(arg0, u16, 6)++;
    func_800478B8(arg2);

    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        n = FIELD(arg0, u16, 4) + 1;
        FIELD(arg0, u16, 4) = n;
        if ((s16)n >= 3) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] = (u32)(D_800814A0[0] | 0x8000);
            func_800249AC();
        }

        func_8003DB94(arg2, D_80025E04, 0);
        if (FIELD(arg2, u8, 0xC) != 0) {
            FIELD(arg2, u8, 0xC) = 0;
            FIELD(arg2, u8, 0xD) = 0x80;
            func_800249AC();
        }
        if (FIELD(arg2, u8, 0xD) != 0) {
            FIELD(arg2, u8, 0xD) = 0;
            FIELD(arg2, u8, 0xE) = 0x80;
            func_800249AC();
        }
        FIELD(arg2, u8, 0xE) = 0;
        FIELD(arg2, u8, 0xC) = 0x80;
    }
}
