#include "common.h"

typedef struct S_80020F68_0 {
    void * unk_00;
    u8 pad_04[0x44];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_80020F68_0;   /* arg0 in func_80020F68; pointer addresses record offset 0x10 */


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
    if (((S_80020F68_0 *)((u8 *)arg0 - 0x10))->unk_4C != 0) {
        ((S_80020F68_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_804081AC;
        return func_80407FBC(arg0);
    }
    ((S_80020F68_0 *)((u8 *)arg0 - 0x10))->unk_50 = 1;
    func_8040316C(arg0 - 0x20, arg0 + 0x38);
    ((S_80020F68_0 *)((u8 *)arg0 - 0x10))->unk_48 = 1;
    ((S_80020F68_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80407F40;
}
