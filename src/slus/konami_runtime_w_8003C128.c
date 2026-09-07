#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003C128_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8003C128_0;   /* temp_v0 in func_8003C128 */


void *func_8003FE78();   /* extern */
extern M2C_UNK D_80082D38;
extern M2C_UNK func_8003C3B4;

void func_8003C128(void) {
    S_8003C128_0 *temp_v0;

    temp_v0 = func_8003FE78(0x15, &D_80082D38, 0x49);
    temp_v0->unk_10 = &func_8003C3B4;
    temp_v0->unk_20 = 0;
}
