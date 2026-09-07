#include "common.h"
#include "m2c_compat.h"

typedef struct S_80614998_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80614998_0;   /* D_80016000 in func_80614998 */

typedef struct S_80614998_1 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_80614998_1;   /* ((S_80614998_0 *)D_80016000)->unk_1C in func_80614998 */




extern S_80614998_0 *D_80016000;


s32 func_80614998(void) {
    return ((S_80614998_1 *)(D_80016000->unk_1C))->unk_38 != 1;
}
