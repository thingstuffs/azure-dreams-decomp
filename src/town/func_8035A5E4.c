#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_8035A5E4_1 {
    u8 pad_00[0x88];
    M2C_UNK (*unk_88)(M2C_UNK);
} S_8035A5E4_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_8035A5E4 */


/* Invoke the callback at offset 0x88 with zero. */
void func_8035A5E4(void) {
    ((S_8035A5E4_1 *)(D_80016000->unk_20))->unk_88(0);
}
