#include "common.h"

extern u8 D_80526650[];
extern s32 func_8003B0B8();

void func_808106A4(void *arg0) {
    u16 value;

    value = *(u16 *)((u8 *)arg0 + 2) + 1;
    *(u16 *)((u8 *)arg0 + 2) = value;
    func_8003B0B8(D_80526650, (s16)value);
}

/* MECHANISM: Declaring D_80526650 as an extern array keeps its address relocatable,
   so gcc emits the lui/addiu after the increment and store instead of holding arg0.
   The ra-only 0x18 frame and the lhu latency nop then fall out naturally. */
