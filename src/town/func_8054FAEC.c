#include "common.h"
#include "m2c_compat.h"

typedef struct S_8054FAEC_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8054FAEC_0;   /* D_80016000 in func_8054FAEC */

typedef struct S_8054FAEC_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8054FAEC_1;   /* ((S_8054FAEC_0 *)D_80016000)->unk_38 in func_8054FAEC */




extern S_8054FAEC_0 *D_80016000;


s32 func_8054FAEC(void) {
    return (u32) ((S_8054FAEC_1 *)(D_80016000->unk_38))->unk_2D5C >= 0x64U;
}
