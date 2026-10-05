#include "common.h"

extern s32 func_8001ADE0(s32 flagIndex);
extern void func_8001ACE8(s32 bit_index);
extern void func_8001AD60(s32 bit_index);
extern u8 D_8001E259[];
extern u8 D_8001E405[];

/* Select a handler and data pointer based on the query for 0xD53. */
void *func_800170B8(void) {
    if (func_8001ADE0(0xD53) != 0) {
        func_8001AD60(0xD53);
        return D_8001E259;
    }
    func_8001ACE8(0xD53);
    return D_8001E405;
}
