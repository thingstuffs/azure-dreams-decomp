#include "common.h"

typedef struct S_80170224_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3E];
    u16 unk_B0;
} S_80170224_0;   /* base in func_80170224 */

typedef struct S_80170224_1 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170224_1;   /* arg0 in func_80170224 */



extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016FCE4(void *, s32, s32, void *);
extern void func_800A9A0C(void *);
extern s16 func_800A2BDC(void *);
extern u16 D_80083462;

s32 func_80170224(S_80170224_1 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    void *base = arg0;
    s16 ret;

    if (((S_80170224_0 *)base)->unk_B0 != 0) {
        ret = func_800ADDA0(arg1, arg2, base, 3, 6, (u8 *)base + 0x9C);
        if (ret < 0) {
            return 0;
        }
        if (arg3 != 0) {
            func_8016FCE4(base, arg1, arg2, base);
            return 0;
        }
    } else {
        ret = 0;
    }

    switch (ret) {
    case 0:
        arg0->unk_9A = 14;
        func_800A9A0C(base);
        return 0;

    case 2:
        func_8016FCE4(arg0, arg1, arg2, base);
        return 0;

    case 1:
        ((S_80170224_0 *)base)->unk_71 &= 0x7F;
        if (func_800A2BDC(base) != 0) {
            ((S_80170224_0 *)base)->unk_46 &= 0x7FFF;
            return 0;
        }
        /* fallthrough */
    default:
        ((S_80170224_0 *)base)->unk_71 &= 0x7F;
        if (!(D_80083462 & 8)) {
            return 1;
        }
        ((S_80170224_0 *)base)->unk_46 &= 0x7FFF;
        return 0;
    }
}
