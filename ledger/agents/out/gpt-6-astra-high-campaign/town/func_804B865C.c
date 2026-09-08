#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016E5C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016E5C_1;   /* temp_v1 in func_80016E5C */

typedef struct S_80016E5C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80016E5C_2;   /* temp_v1_2 in func_80016E5C */


extern Rec_D_80016000 *D_80016000;

/* Scale both position components by 64 and add the 0x220 offset. */
void func_80016E5C(void) {
    S_80016E5C_1 *first_position;
    S_80016E5C_2 *second_position;

    first_position = D_80016000->unk_1C.as_pv;
    first_position->unk_04 = (s32) ((first_position->unk_04 << 6) + 0x220);
    second_position = D_80016000->unk_1C.as_pv;
    second_position->unk_08 = (s32) ((second_position->unk_08 << 6) + 0x220);
}
