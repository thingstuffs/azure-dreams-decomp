#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016930_1 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_80016930_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80016930 */




M2C_UNK func_80018BD0();                     /* extern */
extern Rec_D_80016000 *D_80016000;


s32 func_80016930(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    ((S_80016930_1 *)(D_80016000->unk_20))->unk_2F8(0x10, 0x200);
    return 0;
}
