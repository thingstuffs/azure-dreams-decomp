#include "common.h"
#include "m2c_compat.h"

typedef struct S_8059E6D8_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8059E6D8_0;   /* D_80016000 in func_8059E6D8 */

typedef struct S_8059E6D8_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8059E6D8_1;   /* ((S_8059E6D8_0 *)D_80016000)->unk_38 in func_8059E6D8 */




extern S_8059E6D8_0 *D_80016000;


s32 func_8059E6D8(u32 arg0) {
    return (u32) ((S_8059E6D8_1 *)(D_80016000->unk_38))->unk_2D5C >= arg0;
}
