#include "common.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8040316C(void *arg0, void *arg1);
extern void func_80407FBC(void *arg0);

/* Narrow absolute symbol binds: these two -0x10 stores in the retail asm use
 * lui/addiu (address-of relocation form), not lui/ori (raw int), against two
 * EXE-side code addresses that are not yet named func_ symbols in this repo.
 * Bind them locally as opaque objects at their real linked addresses so the
 * store compiles to the same %hi/%lo(addiu) address computation. */
__asm__(".set D_804081AC, 0x804081AC");
__asm__(".set D_80407F40, 0x80407F40");
extern void *D_804081AC;
extern void *D_80407F40;

void func_80020F68(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x3C) != 0) {
        M2C_FIELD(arg0, void **, -0x10) = &D_804081AC;
        return func_80407FBC(arg0);
    }
    M2C_FIELD(arg0, s32 *, 0x40) = 1;
    func_8040316C(arg0 - 0x20, arg0 + 0x38);
    M2C_FIELD(arg0, s32 *, 0x38) = 1;
    M2C_FIELD(arg0, void **, -0x10) = &D_80407F40;
}
