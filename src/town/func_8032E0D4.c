#include "common.h"
#include "m2c_compat.h"

typedef struct S_800188D4_0 {
    u8 pad_00[0x40];
    void * unk_40;
} S_800188D4_0;   /* D_80016000 in func_800188D4 */

typedef struct S_800188D4_1 {
    u8 pad_00[0x114];
    s8 unk_114;
} S_800188D4_1;   /* ((S_800188D4_0 *)D_80016000)->unk_40 in func_800188D4 */




extern S_800188D4_0 *D_80016000;


void func_800188D4(void) {
    ((S_800188D4_1 *)(D_80016000->unk_40))->unk_114 = 0;
}
