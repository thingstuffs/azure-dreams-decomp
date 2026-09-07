#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C7C88_0 {
    u8 pad_00[0x6E];
    s16 unk_6E;
    u8 pad_70[0x14];
    s16 unk_84;
    s16 unk_86;
    u8 pad_88[0xC];
    s8 unk_94;
} S_800C7C88_0;   /* arg0 in func_800C7C88 */

void func_800C7C88(S_800C7C88_0 *arg0) {
    arg0->unk_84 = 0x520;
    arg0->unk_86 = 0x2A0;
    arg0->unk_94 = 2;
    arg0->unk_6E = 0x400;
}
