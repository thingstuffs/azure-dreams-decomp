#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4(M2C_UNK, void *, s32);          /* extern */
extern M2C_UNK D_80029534;

/* Links nodes in D_80029534 index order until an index reaches 15. */
void func_80027FA4(M2C_UNK nodes) {
    func_800491F4(nodes, &D_80029534, 15);
}
