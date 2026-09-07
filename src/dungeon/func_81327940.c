#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016F140_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8016F140_0;   /* arg0 in func_8016F140 */

void func_8016F140(S_8016F140_0 *arg0) {
    arg0->unk_6D = 0;
    arg0->unk_71 = (u8) (arg0->unk_71 & 0x7F);
    arg0->unk_46 = (u16) (arg0->unk_46 & 0x7FFF);
}
