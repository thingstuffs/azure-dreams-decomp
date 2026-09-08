#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8069778C_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_8069778C_1;   /* temp_a0 in func_8069778C */


extern Rec_D_80016000 *D_80016000;
extern s32 D_80018AE0;

/* Subtracts D_80018AE0 from the linked state's stored value. */
void func_8069778C(void) {
    S_8069778C_1 *state;

    state = D_80016000->unk_38.as_pv;
    state->unk_2D5C = (s32) (state->unk_2D5C - D_80018AE0);
}
