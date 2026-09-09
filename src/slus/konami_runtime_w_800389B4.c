#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800389B4_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800389B4_0;   /* arg0 in func_800389B4 */


M2C_UNK SD_Call();                     /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_80038A10;

/* Triggers action 0xB4 and selects func_80038A10 when the status is not 0x100. */
void func_800389B4(S_800389B4_0 *context) {
    if (func_80053EF0(4) != 0x100) {
        SD_Call(0xB4);
        context->unk_10 = &func_80038A10;
    }
}
