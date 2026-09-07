#include "common.h"
#include "m2c_compat.h"

s32 func_80065420();        /* extern */

typedef struct S_800B0654_0 {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x92];
    s32 unk_C0;
} S_800B0654_0;   /* arg2 in func_800B0654 */

typedef struct S_800B0654_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B0654_1;   /* arg0 in func_800B0654 */

typedef struct S_800B0654_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800B0654_2;   /* arg1 in func_800B0654 */

/* Copy three source values into the destination state and store the adjusted calculation result. */
void func_800B0654(S_800B0654_1 *sourceValues, S_800B0654_2 *resultAdjustment, void *destinationState) {
    ((S_800B0654_0 *)destinationState)->unk_28 = (u16) sourceValues->unk_02;
    ((S_800B0654_0 *)destinationState)->unk_2A = (u16) sourceValues->unk_06;
    ((S_800B0654_0 *)destinationState)->unk_2C = (u16) sourceValues->unk_0A;
    ((S_800B0654_0 *)destinationState)->unk_C0 = (s32) (func_80065420(destinationState + 0x28, destinationState + 0xB8, destinationState + 0x90, destinationState + 0x94) + resultAdjustment->unk_04);
}
