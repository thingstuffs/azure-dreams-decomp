#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_805D21B4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_805D21B4_1;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in func_805D21B4 */




extern Rec_D_80016000 *D_80016000;

void func_805D21B4(void) {
    ((S_805D21B4_1 *)(((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32)))->unk_04 = 0;
}
