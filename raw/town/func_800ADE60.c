#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800AAE98(void *);
extern void func_800AAFE0(void *, s32);
extern s32 func_800AB030(void *);
extern void func_800AB6EC(void);
extern u8 D_800AB408[];
extern u8 D_800AB708[];

void func_800AB5C0(void *arg0, void *arg1) {
    s16 buf[12];
    s32 offset;
    u16 timer;

    if (FIELD(arg0, s16, 0x90) < 100) {
        FIELD(arg0, void *, 0x50) = D_800AB708;
    }
    func_800AAFE0(buf, 4);
    offset = func_800AAE98(arg1);
    buf[5] -= offset + func_800AB030(arg0);
    timer = FIELD(arg0, u16, 0x6C) - 1;
    FIELD(arg0, u16, 0x6C) = timer;
    if ((s16)timer < 0) {
        FIELD(arg1, u16, 0xE) = FIELD(arg1, u16, 2) = buf[1];
        FIELD(arg1, u16, 0x12) = FIELD(arg1, u16, 6) = buf[3];
        FIELD(arg1, u16, 0x16) = FIELD(arg1, u16, 0xA) = buf[5];
        FIELD(arg0, void *, 0x50) = D_800AB408;
        FIELD(arg0, u16, 0x6C) = 150;
        func_800AB6EC();
        return;
    }
    FIELD(arg1, s16, 2) = (FIELD(arg1, s16, 2) + buf[1]) / 2;
    FIELD(arg1, s16, 6) = (FIELD(arg1, s16, 6) + buf[3]) / 2;
    FIELD(arg1, s16, 0xA) = (FIELD(arg1, s16, 0xA) + buf[5]) / 2;
}

/* MECHANISM: A 24-byte s16 stack object keeps the sampled coordinates at
   sp+0x12/+0x16/+0x1A; arg0/arg1 and the cross-call offset form s2/s1/s0.
   Chained copies load each coordinate once; the expired arm restores 150. */
