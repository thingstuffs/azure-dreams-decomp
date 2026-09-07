#include "common.h"
#include "m2c_compat.h"

typedef struct S_806149C0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_806149C0_0;   /* D_80016000 in func_806149C0 */

typedef struct S_806149C0_1 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_806149C0_1;   /* ((S_806149C0_0 *)D_80016000)->unk_1C in func_806149C0 */




extern S_806149C0_0 *D_80016000;


s32 func_806149C0(void) {
    return ((S_806149C0_1 *)(D_80016000->unk_1C))->unk_38 != 2;
}
