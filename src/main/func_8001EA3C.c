#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001EA3C_0 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u8 pad_10[0x34];
    s32 unk_44;
} S_8001EA3C_0;   /* arg0 in func_8001EA3C; pointer addresses record offset 0x10 */


void func_8001EA3C(void *arg0) {
    u16 temp_a1;

    temp_a1 = ((S_8001EA3C_0 *)((u8 *)arg0 - 0x10))->unk_0E;
    if (temp_a1 & 0x2000) {
        ((S_8001EA3C_0 *)((u8 *)arg0 - 0x10))->unk_0E = (u16) (temp_a1 & 0xDFFF);
        ((S_8001EA3C_0 *)((u8 *)arg0 - 0x10))->unk_00 = (s32) ((S_8001EA3C_0 *)((u8 *)arg0 - 0x10))->unk_44;
    }
}
