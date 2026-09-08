#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_804804BC_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_804804BC_1;   /* temp_a0 in func_804804BC */


extern Rec_D_80016000 *D_80016000;
extern s32 D_80019438;

/* Decrements the current state's counter by D_80019438. */
void func_804804BC(void) {
    S_804804BC_1 *counter_state;

    counter_state = D_80016000->unk_38.as_pv;
    counter_state->unk_2D5C = (s32) (counter_state->unk_2D5C - D_80019438);
}
