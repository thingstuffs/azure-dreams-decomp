#include "common.h"
#include "m2c_compat.h"

typedef struct S_8065C424_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8065C424_0;   /* D_80016000 in func_8065C424 */

typedef struct S_8065C424_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_8065C424_1;   /* temp_a0 in func_8065C424 */


extern S_8065C424_0 *D_80016000;
extern s32 D_80018340;

void func_8065C424(void) {
    S_8065C424_1 *temp_a0;

    temp_a0 = D_80016000->unk_38;
    temp_a0->unk_2D5C = (s32) (temp_a0->unk_2D5C - D_80018340);
}
