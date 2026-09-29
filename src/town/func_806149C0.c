#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_806149C0_1 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_806149C0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_806149C0 */






/* Returns whether the referenced record's unk_38 field differs from 2. */
s32 func_806149C0(void) {
    return ((S_806149C0_1 *)(D_80016000->unk_1C))->unk_38 != 2;
}
