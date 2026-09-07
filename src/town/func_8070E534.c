#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80017534_1 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_80017534_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80017534 */




M2C_UNK func_80016CC4();                            /* extern */
M2C_UNK func_80016DBC();                            /* extern */
extern Rec_D_80016000 *D_80016000;


s32 func_80017534(void) {
    func_80016CC4();
    func_80016DBC();
    ((S_80017534_1 *)(D_80016000->unk_20))->unk_2F8(0xE, 0x200);
    return 0;
}
