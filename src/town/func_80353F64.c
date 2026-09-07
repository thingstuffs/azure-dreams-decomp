#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80353F64_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80353F64_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_80353F64 */




extern Rec_D_80016000 *D_80016000;


void func_80353F64(void) {
    ((S_80353F64_1 *)(D_80016000->unk_1C.as_pv))->unk_04 = 0x15;
    ((S_80353F64_1 *)(D_80016000->unk_1C.as_pv))->unk_08 = 0x12;
}
