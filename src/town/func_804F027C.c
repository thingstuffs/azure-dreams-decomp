#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_804F027C_1 {
    u8 pad_00[0x2C0];
    M2C_UNK (*unk_2C0)();
} S_804F027C_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_804F027C */




M2C_UNK func_8001746C();                     /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_800175E4;
extern M2C_UNK *D_80017698;


void func_804F027C(void) {
    ((S_804F027C_1 *)(D_80016000->unk_20))->unk_2C0();
    D_80017698 = &D_800175E4;
    func_8001746C(0x526);
}
