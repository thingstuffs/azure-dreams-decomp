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


/* Advances a three-component interpolation and deactivates it when complete. */
void func_8004D12C(void *record_data) {
    s32 progress;
    u16 delta_x;
    u16 delta_y;
    u16 delta_z;
    S_8004D12C_1 *output;

    output = ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_04;
    progress = ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18 + ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_1C;
    ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18 = progress;
    if (progress >= 0x1000) {
        ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18 = 0x1000;
        ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_00 = 0;
    }
    delta_x = ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_08;
    output->unk_00 = (s16) ((((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_10 - delta_x) + ((s32) ((s16) delta_x * ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18) >> 0xC));
    delta_y = ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_0A;
    output->unk_02 = (s16) ((((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_12 - delta_y) + ((s32) ((s16) delta_y * ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18) >> 0xC));
    delta_z = ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_0C;
    output->unk_04 = (s16) ((((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_14 - delta_z) + ((s32) ((s16) delta_z * ((S_8004D12C_0 *)((u8 *)record_data - 0x4))->unk_18) >> 0xC));
}
