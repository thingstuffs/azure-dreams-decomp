#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80019BB0_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_80019BB0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80019BB0 */




M2C_UNK func_80019B70();                      /* extern */
extern Rec_D_80016000 *D_80016000;
extern u8 D_80017B30;


void func_80019BB0(void) {
    func_80019B70((((S_80019BB0_1 *)(D_80016000->unk_20))->unk_2D4(0) * 8) + &D_80017B30);
}
