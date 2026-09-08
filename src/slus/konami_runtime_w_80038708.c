#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038708_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x1E];
    s8 unk_32;
} S_80038708_0;   /* arg0 in func_80038708 */


extern M2C_UNK D_800DCF54;
extern M2C_UNK func_80038A10;

/* Calls the record's indexed handler, then sets its next handler to func_80038A10. */
void func_80038708(S_80038708_0 *record) {
    ((s32 (*)())(*(s32 *)((u8 *)(&D_800DCF54) + ((record->unk_32) * 4))))();
    record->unk_10 = &func_80038A10;
}
