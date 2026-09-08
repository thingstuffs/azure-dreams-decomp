#include "common.h"

#include "common.h"

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3c;
    s32 f40;
    s32 f44;
    s8 f48;
    u8 f49;
    u8 f4a;
    s8 f4b;
    s8 f4c;
    s8 f4d[3];
} S_80085FA8;

extern s32 D_800737DC[16];
extern s32 func_800589B8(S_80085FA8 *a0);
extern void func_80058E64(void);
extern void func_80058E6C(S_80085FA8 *a0, s32 a1);
extern void func_800590E0(S_80085FA8 *a0);
extern s32 func_8005914C(S_80085FA8 *a0, s32 a1, s32 a2, s32 a3);

s32 func_8005947C(S_80085FA8 *arg0)
{
    s32 s1;
    register s32 s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 s4;
    register s32 s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 ev ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 kind ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u32 idx;
    s32 v0;

    s4 = 0;
    ev = func_800589B8(arg0);
    kind = ev;
    if (!(ev & 0x80)) {
        s1 = arg0->f4a;
        arg0->f49 = 1;
    } else {
        s1 = ev;
        if ((kind & 0xFF) != 0xFF) {
            arg0->f4a = ev;
        }
        arg0->f49 = 0;
    }
    idx = (u32)s1 >> 4;
    s3 = D_800737DC[idx & 0xF];
    if (s3 != 0) {
        if (arg0->f49 != 0) {
            s2 = kind;
        } else {
            s2 = func_800589B8(arg0);
        }
        if (s3 == 2) {
            s4 = func_800589B8(arg0);
        }
        func_8005914C(arg0, s1 & 0xFF, s2 & 0xFF, s4 & 0xFF);
        return 0;
    }
    if ((kind & 0xFF) == 0xF0) {
        goto case_f0;
    }
    if ((kind & 0xFF) != 0xFF) {
        goto otherwise;
    }
    {
        v0 = func_800589B8(arg0);
        func_80058E6C(arg0, v0 & 0xFF);
        return 0;
    }
case_f0:
    func_800590E0(arg0);
    return 0;
otherwise:
    func_80058E64();
    return 0;
}
