#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008D330_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008D330_0;   /* arg0 in func_8008D330 */

void func_8008D330(S_8008D330_0 *arg0) {
    arg0->unk_9A = 0x21;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
}
