#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016F324_0 {
    u8 pad_00[0xBA];
    u8 unk_BA;
} S_8016F324_0;   /* D_80175D50 in func_8016F324 */


extern S_8016F324_0 *D_80175D50;

s32 func_8016F324(s32 arg0) {
    return D_80175D50->unk_BA == arg0;
}
