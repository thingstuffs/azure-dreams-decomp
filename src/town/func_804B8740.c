#include "common.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016F40_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80016F40_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_80016F40 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern Rec_D_80016000 *D_80016000;


/* Set the current record's two state values to 0x560 and 0x3E0. */
void func_80016F40(void) {
    ((S_80016F40_1 *)(D_80016000->unk_1C.as_pv))->unk_04 = 0x560;
    ((S_80016F40_1 *)(D_80016000->unk_1C.as_pv))->unk_08 = 0x3E0;
}
