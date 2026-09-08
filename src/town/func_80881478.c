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

/* Read the selected table value between mode-one setup and completion calls. */
s32 func_80881478(void) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 entry_value;
    s32 entry_index;

    READ_ZERO(zero);
    func_80700868(zero | 1);
    entry_index = D_80700630[0];
    entry_value = *(s32 *)(D_80700000 + (entry_index * 0x10) + 0x674);
    READ_ZERO(zero);
    func_8070096C(entry_index, zero | 1);
    READ_ZERO(zero);
    func_807007D8(zero | 1);
    return entry_value;
}
