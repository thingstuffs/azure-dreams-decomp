#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D21B4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_805D21B4_1;   /* ((D_80016000->unk_08 * 8) + D_80016000->unk_40) in func_805D21B4 */


typedef struct S_805D21B4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_805D21B4_0;   /* D_80016000 in func_805D21B4 */


extern S_805D21B4_0 *D_80016000;

void func_805D21B4(void) {
    ((S_805D21B4_1 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_04 = 0;
}
