#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003F2A4();                         /* extern */

typedef struct S_800B6F54_0 {
    u8 pad_00[0xD0];
    s32 unk_D0;
    s32 unk_D4;
} S_800B6F54_0;   /* arg0 in func_800B6F54 */

/* Processes and clears both nonzero handles, returning whether either was set. */
s32 func_800B6F54(S_800B6F54_0 *owner) {
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
