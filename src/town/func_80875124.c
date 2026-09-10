#include "common.h"
#include "m2c_compat.h"

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                     zero | (value);                                                      }) (value)
#else
#endif

M2C_UNK func_80700C08();                     /* extern */
M2C_UNK func_80701060();                            /* extern */

void func_80875124(void) {
    func_80700C08(({                                                                       register s32 zero ASM_REG("$0");                                     zero | (3);                                                      }));
    func_80701060();
}

/* MECHANISM: The seed already had retail's 24-byte frame, sole $ra save, and two-call CFG.
   A portable guarded hard-$zero ({                                                                       register s32 zero ASM_REG("$0");                                     zero | (3);                                                      }) prevents li/addiu folding and emits retail's
   ori $a0,$zero,3 in the first jal delay slot; every other word stays unchanged. */
