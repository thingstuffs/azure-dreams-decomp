#include "common.h"
#include "m2c_compat.h"

typedef struct S_806DB17C_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_806DB17C_0;   /* D_80016000 in func_806DB17C */

typedef struct S_806DB17C_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_806DB17C_1;   /* ((S_806DB17C_0 *)D_80016000)->unk_38 in func_806DB17C */




u32 func_80016134();                                /* extern */
extern S_806DB17C_0 *D_80016000;


s32 func_806DB17C(void) {
    return (u32) ((S_806DB17C_1 *)(D_80016000->unk_38))->unk_2D5C >= func_80016134();
}
