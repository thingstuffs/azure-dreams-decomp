#include "common.h"

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) __asm__("" : "=r"(var))
#endif

extern s32 D_80700630[];
extern u8 D_80700000[];
extern void func_807007D8(s32);
extern void func_80700868(s32);
extern void func_8070096C(s32, s32);

s32 func_80881478(void) {
    register s32 zero ASM_REG("$0");
    s32 value;
    s32 index;

    READ_ZERO(zero);
    func_80700868(zero | 1);
    index = D_80700630[0];
    value = *(s32 *)(D_80700000 + (index * 0x10) + 0x674);
    READ_ZERO(zero);
    func_8070096C(index, zero | 1);
    READ_ZERO(zero);
    func_807007D8(zero | 1);
    return value;
}
