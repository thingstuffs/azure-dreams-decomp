#include "common.h"
#include "m2c_compat.h"

typedef struct S_801720D0_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801720D0_0;   /* arg1 in func_801720D0 */

typedef struct S_801720D0_1 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801720D0_1;   /* arg0 in func_801720D0; pointer addresses record offset 0x2 */


M2C_UNK func_80171F30(); /* extern */
extern s32 D_800814A0[3];

void func_801720D0(void *arg0, S_801720D0_0 *arg1) {
    u16 temp_v0;

    arg1->unk_0A = (u16) (arg1->unk_0A - 4);
    if (!(((S_801720D0_1 *)((u8 *)arg0 - 0x2))->unk_18 & 1)) {
        func_80171F30(arg0 - 0x20, 0x8080, 8, 0);
    }
    temp_v0 = ((S_801720D0_1 *)((u8 *)arg0 - 0x2))->unk_18 - 1;
    ((S_801720D0_1 *)((u8 *)arg0 - 0x2))->unk_18 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_801720D0_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_801720D0_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
