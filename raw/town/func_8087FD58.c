#include "common.h"

extern s32 func_80701090();
extern s32 D_807009E4[];

#ifdef NON_MATCHING
#define OR_ZERO(value) (value)
#else
#define OR_ZERO(value)                                                      \
    ({                                                                      \
        register s32 zero ASM_REG("$0");                                   \
        ASM_KEEP(zero);                                                     \
        zero | (value);                                                     \
    })
#endif

void func_8087FD58(s32 arg0, s32 arg1) {
    if (D_807009E4[((arg0 * 7) + arg1) * 2] & 1) {
        func_80701090(OR_ZERO(0x152));
    }
}
