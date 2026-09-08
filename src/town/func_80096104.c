#include "common.h"

extern u8 D_80083498[];
extern void func_80093D48(void *, s32, s32);

/* Initialize the global context record using its two stored values. */
void func_80093864(void) {
    u8 *context = D_80083498;
    func_80093D48(context + 0x20,
                  *(s32 *)(context + 8),
                  *(s32 *)(context + 0xC));
}
