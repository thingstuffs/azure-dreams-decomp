#include "common.h"

extern void func_8004DA74(s32 base_addr, void *data, s32 mode);
extern u8 D_800282CC[];

/* Processes data at base offset 0x7C using D_800282CC and mode 1. */
void func_80027054(s32 base_addr) {
    func_8004DA74(base_addr + 0x7C, &D_800282CC[0], 1);
}
