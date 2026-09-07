#include "common.h"
#include "m2c_compat.h"

typedef struct S_800187F0_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800187F0_0;   /* D_80016000 in func_800187F0 */

typedef struct S_800187F0_1 {
    u8 pad_00[0x1E8];
    M2C_UNK (*unk_1E8)(M2C_UNK);
} S_800187F0_1;   /* ((S_800187F0_0 *)D_80016000)->unk_20 in func_800187F0 */




extern S_800187F0_0 *D_80016000;


void func_800187F0(void) {
    ((S_800187F0_1 *)(D_80016000->unk_20))->unk_1E8(7);
}
