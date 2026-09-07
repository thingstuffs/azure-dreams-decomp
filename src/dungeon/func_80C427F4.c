#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173FF4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80173FF4_0;   /* arg1 in func_80173FF4 */

typedef struct S_80173FF4_1 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} S_80173FF4_1;   /* arg0 in func_80173FF4; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                     /* extern */
extern s32 D_800814A0[3];

void func_80173FF4(void *arg0, S_80173FF4_0 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_08 = (s32) (arg1->unk_08 + 0x10000);
    func_800478B8(arg2);
    temp_v0 = ((S_80173FF4_1 *)((u8 *)arg0 - 0x2))->unk_1C - 1;
    ((S_80173FF4_1 *)((u8 *)arg0 - 0x2))->unk_1C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_80173FF4_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_80173FF4_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
