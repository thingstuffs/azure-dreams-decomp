#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8004D12C_0 {
    s32 unk_00;
    void * unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s32 unk_1C;
} S_8004D12C_0;   /* arg0 in func_8004D12C; pointer addresses record offset 0x4 */

typedef struct S_8004D12C_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_8004D12C_1;   /* temp_a2 in func_8004D12C */


void func_8004D12C(void *arg0) {
    s32 temp_v0;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_a0_3;
    S_8004D12C_1 *temp_a2;

    temp_a2 = ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_04;
    temp_v0 = ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18 + ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_1C;
    ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18 = temp_v0;
    if (temp_v0 >= 0x1000) {
        ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18 = 0x1000;
        ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_00 = 0;
    }
    temp_a0 = ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_08;
    temp_a2->unk_00 = (s16) ((((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_10 - temp_a0) + ((s32) ((s16) temp_a0 * ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18) >> 0xC));
    temp_a0_2 = ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_0A;
    temp_a2->unk_02 = (s16) ((((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_12 - temp_a0_2) + ((s32) ((s16) temp_a0_2 * ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18) >> 0xC));
    temp_a0_3 = ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_0C;
    temp_a2->unk_04 = (s16) ((((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_14 - temp_a0_3) + ((s32) ((s16) temp_a0_3 * ((S_8004D12C_0 *)((u8 *)arg0 - 0x4))->unk_18) >> 0xC));
}
