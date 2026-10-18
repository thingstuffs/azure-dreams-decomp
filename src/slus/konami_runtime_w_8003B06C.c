#include "common.h"
#include "m2c_compat.h"

#include "common.h"
s32 func_8003C758(s32 key);                   /* extern */
extern M2C_UNK D_80080F40;
extern M2C_UNK D_80080F60;
extern M2C_UNK D_80081010;

/* Applies func_8003C758 to the three global runtime objects. */
void func_8003B06C(void) {
    func_8003C758(&D_80080F40);
    func_8003C758(&D_80081010);
    func_8003C758(&D_80080F60);
}
