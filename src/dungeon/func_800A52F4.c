#include "common.h"

extern s16 D_80083228[];

extern void func_80042518(void *arg0, s32 arg1);
extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_80047784(void *arg0, s32 arg1, s32 arg2);

void func_800AAA54(void *arg0, void *arg1, void *arg2, u8 *arg3) {
    *((u8 *) arg0 + 0x9A) = 8;
    *((u8 *) arg0 + 0x9B) = 0;
    *(s32 *) ((u8 *) arg0 + 0x8C) = 0;
    *(s32 *) ((u8 *) arg2 + 0x2C) = (s32) arg3;
    if (arg3 != 0) {
        func_80047784(arg2, arg3[(s32) (D_80083228[0] + *(s16 *) ((u8 *) arg0 + 0x2A) + 0x100) >> 9 & 7], 0);
    }
    *(s32 *) ((u8 *) arg0 + 0x1C) = *(s32 *) ((u8 *) arg0 + 0x1C) | 0x04000000;
    func_80042B68(arg0, 4);
    if ((func_80042900(arg0, 0xA) << 0x10) != 0) {
        *((u8 *) arg0 + 0x13) = *((u8 *) arg0 + 0xA8);
        func_80042518(arg0, 0xA);
    }
    *(s16 *) ((u8 *) arg0 + 0x96) = 0x40;
}
