#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_80016424_1 {
    u8 pad_00[0x344];
    M2C_UNK (*unk_344)(M2C_UNK *, M2C_UNK);
} S_80016424_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80016424 */


extern M2C_UNK D_8001BF80;


/* Pass D_8001BF80 and 0x14 to the object callback. */
void func_80016424(void) {
    ((S_80016424_1 *)(D_80016000->unk_20))->unk_344(&D_8001BF80, 0x14);
}
