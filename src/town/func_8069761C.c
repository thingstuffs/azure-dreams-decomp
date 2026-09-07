#include "common.h"

typedef struct S_8069761C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8069761C_0;   /* D_80016000 in func_8069761C */


typedef s32 M2C_UNK;

typedef struct S_8069761C_1 {
    u8 pad_00[0x68];
    s32 (*unk_68)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
} S_8069761C_1;   /* D_80016000->unk_20 in func_8069761C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

M2C_UNK func_800165C4();
extern S_8069761C_0 *D_80016000;
extern M2C_UNK D_80018AE8;
extern s32 D_80018BE8;

void func_8069761C(void) {
    register s32 zero LOCAL_ASM_REG("$4");

    func_800165C4(&D_80018AE8);

    zero = 0;
    LOCAL_ASM_KEEP(zero);
    D_80018BE8 = ((S_8069761C_1 *)(D_80016000->unk_20))->unk_68(zero, zero, 2, &D_80018AE8);
}
