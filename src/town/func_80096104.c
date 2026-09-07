#include "common.h"

extern u8 D_80083498[];
extern void func_80093D48(void *, s32, s32);

void func_80093864(void) {
    u8 *base = D_80083498;
    func_80093D48(base + 0x20,
                  *(s32 *)(base + 8),
                  *(s32 *)(base + 0xC));
}
