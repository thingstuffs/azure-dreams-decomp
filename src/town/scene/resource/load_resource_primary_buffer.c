#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/resource.h"
void func_8001E578(s32);                     /* extern */
extern M2C_UNK D_80021F20;

/* Calls func_8001E578 with 0x400 and returns the address of D_80021F20. */
s32 *load_resource_400_primary_buffer(void) {
    func_8001E578(F_sbs01_pad11);
    return &D_80021F20;
}
