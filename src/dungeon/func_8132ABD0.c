#include "common.h"
#include "m2c_compat.h"

typedef struct S_801723D0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801723D0_0;   /* arg1 in func_801723D0 */

typedef struct S_801723D0_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_801723D0_1;   /* arg2 in func_801723D0 */

typedef struct S_801723D0_2 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801723D0_2;   /* arg0 in func_801723D0; pointer addresses record offset 0x2 */


M2C_UNK func_80171F30(); /* extern */
extern s32 D_800814A0[3];

void func_801723D0(void *arg0, S_801723D0_0 *arg1, S_801723D0_1 *arg2) {
    s32 temp_s0;
    u16 temp_v0;

    temp_s0 = arg0 - 0x20;
    arg1->unk_02 = (u16) (arg1->unk_02 + 0x10);
    arg2->unk_1A = (u16) (arg2->unk_1A + 0x1F4);
    func_80171F30(temp_s0, 0x8080, 0x1C, 1);
    func_80171F30(temp_s0, 0x8080, 0x1C, 1);
    func_80171F30(temp_s0, 0x8080, 0x1C, 1);
    func_80171F30(temp_s0, 0x8080, 0x1C, 2);
    func_80171F30(temp_s0, 0x8080, 0x1C, 2);
    func_80171F30(temp_s0, 0x8080, 0x1C, 2);
    temp_v0 = ((S_801723D0_2 *)((u8 *)arg0 - 0x2))->unk_18 - 1;
    ((S_801723D0_2 *)((u8 *)arg0 - 0x2))->unk_18 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_801723D0_2 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_801723D0_2 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
