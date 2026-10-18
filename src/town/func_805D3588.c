#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


s32 func_800193E0(s32);
s32 func_80019458(s32);
extern M2C_UNK D_80019890;


/* Dispatches IDs 0x3EB and 0x631, then invokes object callbacks with 0 and &D_80019890. */
void func_805D3588(void) {
    func_800193E0(0x3EB);
    func_80019458(0x631);
    ((s32 (*) (s32))D_80016000->unk_20->callback_084)(0);
    ((s32 (*) (s32 *))D_80016000->unk_20->callback_218)(&D_80019890);
}
