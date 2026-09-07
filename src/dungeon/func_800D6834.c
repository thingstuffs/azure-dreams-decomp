#include "common.h"

extern s16 D_80081468[3];
extern void func_800DBD5C(s16 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_800DBF94(s32 *arg0) {
    if (D_80081468[2] != *arg0) {
        func_800DBD5C(D_80081468[2], *arg0, 2, 0x18C, 0x1B8, 0);
        *arg0 = D_80081468[2];
    }
}
