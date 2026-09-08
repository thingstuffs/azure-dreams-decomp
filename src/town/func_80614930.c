#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80614930_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80614930_1;   /* temp_v1 in func_80614930 */

typedef struct S_80614930_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80614930_2;   /* temp_v1_2 in func_80614930 */


extern Rec_D_80016000 *D_80016000;

/* Advance the two position components by their corresponding increments. */
void func_80614930(void) {
    S_80614930_1 *x_state;
    S_80614930_2 *y_state;

    x_state = D_80016000->unk_1C.as_pv;
    x_state->unk_04 = (s32) (x_state->unk_04 + x_state->unk_10);
    y_state = D_80016000->unk_1C.as_pv;
    y_state->unk_08 = (s32) (y_state->unk_08 + y_state->unk_14);
}
