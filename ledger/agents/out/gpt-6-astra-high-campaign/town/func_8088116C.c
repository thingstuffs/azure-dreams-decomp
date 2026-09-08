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

/* Call func_80700CD0 with 0x278 when the selected entry has bit zero set. */
void func_8088116C(s32 row, s32 column) {
    s32 offset = (column * 8) + (row * 16);

    if (*(s32 *)(D_80700670 + offset) & 1) {
        func_80700CD0(OR_ZERO(0x278));
    }
}
