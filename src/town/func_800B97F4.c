#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

M2C_UNK func_8003F2A4();                         /* extern */


/* Processes and clears both nonzero handles, returning whether either was set. */
s32 func_800B6F54(Rec_func_800B683C_arg0 *owner) {
    s32 firstHandle;
    s32 secondHandle;
    s32 hadHandle;

    firstHandle = owner->unk_D0;
    hadHandle = 0;
    if (firstHandle != 0) {
        func_8003F2A4(firstHandle);
        owner->unk_D0 = 0;
        hadHandle = 1;
    }
    secondHandle = owner->unk_D4;
    if (secondHandle != 0) {
        func_8003F2A4(secondHandle);
        owner->unk_D4 = 0;
        hadHandle = 1;
    }
    return hadHandle;
}
