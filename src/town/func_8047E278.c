#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8047E278_2 {
    u8 pad_00[0x26C];
    M2C_UNK (*unk_26C)(M2C_UNK *, s32);
} S_8047E278_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_8047E278 */




extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_8001601C;

void func_8047E278(void) {
    ((S_8047E278_2 *)(((Rec_D_80016000 *)D_80016000)->unk_20))->unk_26C(&D_8001601C, D_80016000->unk_38.as_s32 + 0x20C);
}
