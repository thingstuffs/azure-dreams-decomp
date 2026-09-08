#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B4350_1 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_800B4350_1;   /* arg0 in func_800B4350 */

typedef struct S_800B4350_2 {
    u8 pad_00[0x78];
    s32 * unk_78;
    s32 * unk_7C;
} S_800B4350_2;   /* ((S_800B4350_1 *)arg0)->unk_5C in func_800B4350 */

typedef struct S_800B4350_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B4350_3;   /* ((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_78 in func_800B4350 */

typedef struct S_800B4350_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B4350_4;   /* ((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_7C in func_800B4350 */

typedef struct S_800B4350_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B4350_5;   /* ((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_78))->unk_04 in func_800B4350 */

typedef struct S_800B4350_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B4350_6;   /* ((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_7C))->unk_04 in func_800B4350 */




typedef struct S_800B4350_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B4350_0;   /* arg0 in func_800B4350 */

/* Initializes two child entries with data addresses and coordinate offsets. */
void func_800B4350(S_800B4350_0 *owner) {
    *((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78 = owner->unk_20 + 0x48;
    ((S_800B4350_5 *)(((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78))->unk_04))->unk_08 = -0x20;
    ((S_800B4350_5 *)(((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78))->unk_04))->unk_0A = -0x18;
    *((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C = owner->unk_20 + 0x90;
    ((S_800B4350_6 *)(((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C))->unk_04))->unk_08 = -0x70;
    ((S_800B4350_6 *)(((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C))->unk_04))->unk_0A = -0x18;
}
