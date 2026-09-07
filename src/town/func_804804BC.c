#include "common.h"
#include "m2c_compat.h"

typedef struct S_804804BC_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_804804BC_0;   /* D_80016000 in func_804804BC */

typedef struct S_804804BC_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_804804BC_1;   /* temp_a0 in func_804804BC */


extern S_804804BC_0 *D_80016000;
extern s32 D_80019438;

void func_804804BC(void) {
    S_804804BC_1 *temp_a0;

    temp_a0 = D_80016000->unk_38;
    temp_a0->unk_2D5C = (s32) (temp_a0->unk_2D5C - D_80019438);
}
