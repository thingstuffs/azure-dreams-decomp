#include "common.h"

extern u8 D_80526650[];
extern s32 func_8003B0B8();

/* Increment the record counter and pass it to the resource handler. */
void func_808106A4(void *record) {
    u16 counter;

    counter = *(u16 *)((u8 *)record + 2) + 1;
    *(u16 *)((u8 *)record + 2) = counter;
    func_8003B0B8(D_80526650, (s16)counter);
}

/* MECHANISM: Declaring D_80526650 as an extern array keeps its address relocatable,
   so gcc emits the lui/addiu after the increment and store instead of holding arg0.
   The ra-only 0x18 frame and the lhu latency nop then fall out naturally. */
