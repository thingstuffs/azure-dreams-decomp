#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8001A6DC_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8001A6DC_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_8001A6DC */




extern Rec_D_80016000 *D_80016000;


/* Stores two values scaled by 32 in the current record's auxiliary data. */
void func_8001A6DC(M2C_UNK unused, s32 value_04, s32 value_08) {
    ((S_8001A6DC_1 *)(D_80016000->unk_1C.as_pv))->unk_04 = (s32) (value_04 << 5);
    ((S_8001A6DC_1 *)(D_80016000->unk_1C.as_pv))->unk_08 = (s32) (value_08 << 5);
}
