#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171470_0 {
    u8 pad_00[0xD2];
    u16 unk_D2;
} S_80171470_0;   /* D_80174CD8 in func_80171470 */


extern S_80171470_0 *D_80174CD8;

s32 func_80171470(void) {
    return D_80174CD8->unk_D2 == 0;
}
