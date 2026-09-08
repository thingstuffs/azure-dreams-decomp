#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8065C424_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_8065C424_1;   /* temp_a0 in func_8065C424 */


extern Rec_D_80016000 *D_80016000;
extern s32 D_80018340;

/* Subtract D_80018340 from the current record's linked state value. */
void func_8065C424(void) {
    S_8065C424_1 *state;

    state = D_80016000->unk_38.as_pv;
    state->unk_2D5C = (s32) (state->unk_2D5C - D_80018340);
}
