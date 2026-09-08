#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B06C0_0 {
    u8 pad_00[0xB8];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    s32 unk_C0;
} S_800B06C0_0;   /* arg2 in func_800B06C0 */

typedef struct S_800B06C0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800B06C0_1;   /* arg0 in func_800B06C0 */

typedef struct S_800B06C0_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800B06C0_2;   /* arg1 in func_800B06C0 */

/* Copy two base values and combine the base and offset into the output. */
void func_800B06C0(S_800B06C0_1 *base_values, S_800B06C0_2 *offset_values, S_800B06C0_0 *output) {
    output->unk_B8 = (u16) base_values->unk_02;
    output->unk_BA = (u16) base_values->unk_06;
    output->unk_C0 = (s32) (base_values->unk_0A + offset_values->unk_04);
}
