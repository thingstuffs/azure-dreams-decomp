#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003C758();                   /* extern */
extern M2C_UNK D_80080F40;
extern M2C_UNK D_80080F60;
extern M2C_UNK D_80081010;

void func_8003B06C(void) {
    func_8003C758(&D_80080F40);
    func_8003C758(&D_80081010);
    func_8003C758(&D_80080F60);
}
