#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80029534;

/* Links nodes in D_80029534 index order until an index reaches 15. */
void func_80027FA4(S_800491F4 **nodes) {
    func_800491F4(nodes, &D_80029534, 15);
}
