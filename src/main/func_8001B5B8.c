#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001B5B8_0 {
    u8 unk_00;
    s8 unk_01;
    u8 pad_02[0x2];
    s32 unk_04;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
} S_8001B5B8_0;   /* arg1 in func_8001B5B8 */

void *func_8001B5B8(void *arg0, void *arg1, s32 arg2) {
    ((S_8001B5B8_0 *)arg1)->unk_01 = 0x28;
    ((S_8001B5B8_0 *)arg1)->unk_0A = (s8) ((arg2 * 0xC) + 4);
    ((S_8001B5B8_0 *)arg1)->unk_0B = 0x15;
    ((S_8001B5B8_0 *)arg1)->unk_04 = 0x800000;
    ((S_8001B5B8_0 *)arg1)->unk_00 = (u8) (((S_8001B5B8_0 *)arg1)->unk_00 | 0x80);
    return arg1 + 0xC;
}
