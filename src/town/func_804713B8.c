#include "common.h"
#include "m2c_compat.h"

typedef struct S_804713B8_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_804713B8_0;   /* D_80016000 in func_804713B8 */

typedef struct S_804713B8_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_804713B8_1;   /* temp_a0 in func_804713B8 */


extern S_804713B8_0 *D_80016000;
extern s32 D_8001B210;

void func_804713B8(void) {
    S_804713B8_1 *temp_a0;

    temp_a0 = D_80016000->unk_38;
    temp_a0->unk_2D5C = (s32) (temp_a0->unk_2D5C + D_8001B210);
}
