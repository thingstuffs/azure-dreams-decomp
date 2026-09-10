#include "common.h"

extern s32 func_80701090();
extern s32 D_807009E4[];

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                     zero | (value);                                                      }) (value)
#else
#endif

/* Call func_80701090 with 0x152 when the selected grid entry has bit zero set. */
void func_8087FD58(s32 row, s32 column) {
    if (D_807009E4[((row * 7) + column) * 2] & 1) {
        func_80701090(({                                                                       register s32 zero ASM_REG("$0");                                     zero | (0x152);                                                      }));
    }
}
