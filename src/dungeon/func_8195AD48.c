#include "common.h"

extern void func_80065820(void *, void *);
extern void func_80064BC0(void *, s32 *);

void func_8195AD48(void *arg0, void *arg1) {
    s32 position[3];

    func_80065820(arg1, arg0);
    position[0] = *(s16 *)((u8 *)arg1 + 0x10);
    position[1] = *(s16 *)((u8 *)arg1 + 0x12);
    position[2] = *(s16 *)((u8 *)arg1 + 0x14);
    func_80064BC0(arg0, position);
    *(s32 *)((u8 *)arg0 + 0x14) = *(s16 *)((u8 *)arg1 + 8);
    *(s32 *)((u8 *)arg0 + 0x18) = *(s16 *)((u8 *)arg1 + 0xA);
    *(s32 *)((u8 *)arg0 + 0x1C) = *(s16 *)((u8 *)arg1 + 0xC);
}
