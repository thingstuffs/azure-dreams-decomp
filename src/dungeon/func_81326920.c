#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016E120_0 {
    u8 pad_00[0xD2];
    u8 unk_D2;
} S_8016E120_0;   /* D_80174704 in func_8016E120 */


extern S_8016E120_0 *D_80174704;

s32 func_8016E120(void) {
    return D_80174704->unk_D2 == 0;
}
