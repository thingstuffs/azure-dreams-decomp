#include "common.h"
#include "m2c_compat.h"

typedef struct S_801740E4_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801740E4_0;   /* arg1 in func_801740E4 */

typedef struct S_801740E4_1 {
    u16 unk_00;
    u8 pad_02[0x14];
    s16 unk_16;
    u8 pad_18[0x1C];
    s16 unk_34;
} S_801740E4_1;   /* arg0 in func_801740E4; pointer addresses record offset 0x2 */

typedef struct S_801740E4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801740E4_2;   /* arg2 in func_801740E4 */


s32 rand();
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[3];

void func_801740E4(void *arg0, S_801740E4_0 *arg1, S_801740E4_2 *arg2) {
    s16 temp_v0;
    s32 random_v0;
    s32 field_v1;

    arg1->unk_00 += ((D_8006CCD8[((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_16] * ((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    arg1->unk_04 += ((D_8006CCE8[((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_16] * ((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    random_v0 = rand();
    field_v1 = arg1->unk_08 + (s32) 0xFFFE0000;
    arg1->unk_08 = field_v1 - (random_v0 & 0xFFF);
    temp_v0 = (u16) ((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_34 - 8;
    ((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_34 = temp_v0;
    if (((temp_v0 << 0x10) <= 0) || (arg2->unk_14 & 0x8000)) {
        ((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_801740E4_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
