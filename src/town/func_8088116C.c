#include "common.h"

extern void func_80700CD0(s32);
extern u8 D_80700670[];

#ifdef NON_MATCHING
#define OR_ZERO(value) (value)
#else
#define OR_ZERO(value)                                                      \
    ({                                                                      \
        register s32 zero ASM_REG("$0");                                   \
        \
        zero | (value);                                                     \
    })
#endif

void func_8088116C(s32 arg0, s32 arg1) {
    s32 offset = (arg1 * 8) + (arg0 * 16);

    if (*(s32 *)(D_80700670 + offset) & 1) {
        func_80700CD0(OR_ZERO(0x278));
    }
}
