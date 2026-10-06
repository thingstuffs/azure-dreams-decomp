#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_8002808C;

/* Links nodes in the order specified by D_8002808C, stopping at an index of 4 or greater. */
void func_80026DC8(S_800491F4 **nodes) {
    func_800491F4(nodes, &D_8002808C, 4);
}
