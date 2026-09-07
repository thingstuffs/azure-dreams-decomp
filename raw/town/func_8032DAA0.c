#include "common.h"

extern u8 *func_80019DFC();
extern s32 func_8001ADE0();
extern u8 D_8001BDB4[16];
extern u8 D_8001C354[16];
extern u8 D_8001E20F[16];

u8 *func_800182A0(void *arg0, s32 arg1, s32 arg2) {
    u8 *value;

    value = func_80019DFC(D_8001BDB4, D_8001C354, arg0, arg2);
    if (func_8001ADE0(0x12C2) != 0) {
        if (func_8001ADE0(*(s16 *)((u8 *)arg0 + 0x18)) != 0) {
            value = D_8001E20F;
        }
    }
    return value;
}
