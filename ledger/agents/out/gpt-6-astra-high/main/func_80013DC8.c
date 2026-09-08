#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4();          /* extern */
extern M2C_UNK D_8002808C;

/* Links nodes in the order specified by D_8002808C, stopping at an index of 4 or greater. */
void func_80026DC8(M2C_UNK nodes) {
    func_800491F4(nodes, &D_8002808C, 4);
}
