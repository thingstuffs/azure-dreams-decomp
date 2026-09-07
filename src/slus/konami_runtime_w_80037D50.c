#include "common.h"

#include "common.h"

extern u8 D_8006A908[];
extern s32 D_8006A8B4[];

void func_80037D50(u8 *arg0) {
    u8 *obj = arg0 + 0x8C;

    obj[0x25] = D_8006A908[arg0[2]];
    *(s16 *)(obj + 0x0E) = D_8006A8B4[obj[0x2A]] * obj[0x25];
}
