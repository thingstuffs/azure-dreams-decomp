#include "common.h"
#include "m2c_compat.h"

s32 func_800AB030();                             /* extern */
s32 func_800C2AE8();                          /* extern */

typedef struct S_800C8194_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800C8194_0;   /* arg1 in func_800C8194 */

void func_800C8194(s32 arg0, S_800C8194_0 *arg1) {
    s32 temp_v0;
    s32 temp_s0;

    temp_s0 = func_800C2AE8(arg1);
    temp_v0 = func_800AB030(arg0);
    temp_v0 -= 0x4C;
    arg1->unk_0A = (s16) (temp_s0 + temp_v0);
}
