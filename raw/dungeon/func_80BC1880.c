#include "common.h"

typedef long long s64;

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 D_800814A0[3];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

void func_80BC1880(void *arg0, void *arg1, void *arg2)
{
    StackWork work;
    s16 count;

    FIELD(arg2, u16, 0x1C) -= 500;
    FIELD(arg2, u16, 0x1E) -= 500;
    FIELD(arg2, u16, 0x1A) += 400;

    FIELD(arg2, s8, 0xC) =
        FIELD(arg0, u8, 2) *
        (FIELD(arg0, s16, 0x1C) - FIELD(arg0, s16, 0x1A)) /
        FIELD(arg0, s16, 0x1C);
    FIELD(arg2, s8, 0xD) =
        FIELD(arg0, u8, 3) *
        (FIELD(arg0, s16, 0x1C) - FIELD(arg0, s16, 0x1A)) /
        FIELD(arg0, s16, 0x1C);
    FIELD(arg2, s8, 0xE) =
        FIELD(arg0, u8, 4) *
        (FIELD(arg0, s16, 0x1C) - FIELD(arg0, s16, 0x1A)) /
        FIELD(arg0, s16, 0x1C);

    work.xyz[0] = FIELD(arg1, u16, 2);
    work.xyz[1] = FIELD(arg1, u16, 6);
    work.xyz[2] = FIELD(arg1, u16, 0xA);
    FIELD(arg2, s16, 6) =
        func_80065420(work.xyz, &work.out18, &work.out20, &work.out24) - 8;

    count = FIELD(arg0, u16, 0x1A) - 1;
    FIELD(arg0, u16, 0x1A) = count;
    if ((count << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
