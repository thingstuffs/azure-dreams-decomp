#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#endif

void func_800165C4();
extern M2C_UNK D_80018AE8;
extern s32 D_80018BE8;

/* Initialize the shared data and store the mode-2 callback result. */
void func_8069761C(void) {
    register s32 zero LOCAL_ASM_REG("$4");

    func_800165C4(&D_80018AE8);

    zero = 0;
    D_80018BE8 = D_80016000->unk_20->callback_068(zero, zero, 2, &D_80018AE8);
}
