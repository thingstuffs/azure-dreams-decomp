#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80016A38();
void func_80016948();
extern M2C_UNK D_80019440;
extern s32 D_80019540;

/* Prepare D_80019440 for the callback and store its result in D_80019540. */
void func_804803D8(void) {
    func_80016948(&D_80019440, 0x100);
    func_80016A38(&D_80019440);
    D_80019540 = D_80016000->unk_20->callback_068(0, 1, 2, &D_80019440);
}
