#include "common.h"

extern void func_8001A1A0(void *, void *);
extern void func_8001A200(void *, void *);

extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;

void *func_8001A9B4(s32 arg0) {
    u8 *base = &D_80017D50;

    if (arg0 != 0) {
        *(s16 *)(base + (arg0 * 0x14) + 2) = 0x400;
    }

    func_8001A200(base, &D_80017ADC);
    func_8001A1A0(base, &D_80017AE8);

    if (arg0 == 1) {
        *(s16 *)(base + 0xA2) = 0x400;
        func_8001A1A0(base + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(base + 0xB6) = 0x400;
        func_8001A1A0(base + 0xB4, &D_80017B0C);
    }

    func_8001A1A0(base + 0xDC, &D_80017AF4);
    func_8001A1A0(base + 0xC8, &D_80017B18);
    return base;
}

/* MECHANISM: A named byte-pointer base holds D_80017D50 in s0 across all calls,
   while arg0 remains in s1, yielding the retail 0x20 frame and save order.
   The apparent j func_8001AA3C is a row-local join: both arms prepare arguments
   for one shared func_8001A1A0 call, reproducing its jump and nop delay slot. */
