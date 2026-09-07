#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80017F8C_1 {
    u8 pad_00[0x21C];
    M2C_UNK (*unk_21C)(M2C_UNK *);
} S_80017F8C_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80017F8C */




extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_8001C0FC;


void func_80017F8C(void) {
    ((S_80017F8C_1 *)(D_80016000->unk_20))->unk_21C(&D_8001C0FC);
}
