#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_800188EC_1 {
    u8 pad_00[0x114];
    u8 unk_114;
} S_800188EC_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_40.as_pv in func_800188EC */






/* Returns the byte at offset 0x114 in the referenced record. */
u8 func_800188EC(void) {
    return ((S_800188EC_1 *)(D_80016000->unk_40))->unk_114;
}
