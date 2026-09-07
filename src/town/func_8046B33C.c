#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C33C_0 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_8001C33C_0;   /* D_8001E950 in func_8001C33C */


extern S_8001C33C_0 *D_8001E950;

s32 func_8001C33C(void) {
    return D_8001E950->unk_04 == 3;
}
