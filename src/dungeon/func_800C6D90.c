#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CC4F0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_800CC4F0_0;   /* arg1 in func_800CC4F0 */

typedef struct S_800CC4F0_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_800CC4F0_1;   /* arg0 in func_800CC4F0; pointer addresses record offset 0x2 */


s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_800CC5F0(); /* extern */
extern s32 D_800814A0[3];

void func_800CC4F0(void *arg0, S_800CC4F0_0 *arg1) {
    u16 temp_v0;

    arg1->unk_0E = (u16) (arg1->unk_0E + (func_80064584(((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_06) >> 6));
    arg1->unk_12 = (u16) (arg1->unk_12 + (func_800644B8(((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_06) >> 6));
    if (((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_08 == 0) {
        func_800CC5F0((u16) arg1->unk_02 >> 6, (u16) arg1->unk_06 >> 6, arg1->unk_0A, ((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_06, 0, 1);
        func_800CC5F0((u16) arg1->unk_02 >> 6, (u16) arg1->unk_06 >> 6, arg1->unk_0A, ((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_06, 1, 1);
    }
    temp_v0 = ((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
    ((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_04 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800CC4F0_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
