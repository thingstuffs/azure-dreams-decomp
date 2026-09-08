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

/* Updates randomized movement, reduces speed, and flags completion when speed expires or a stop is requested. */
void func_801740E4(void *object_data, S_801740E4_0 *position, S_801740E4_2 *state) {
    s16 next_speed;
    s32 random_value;
    s32 lowered_z;

    position->unk_00 += ((D_8006CCD8[((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_16] * ((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    position->unk_04 += ((D_8006CCE8[((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_16] * ((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    random_value = rand();
    lowered_z = position->unk_08 + (s32) 0xFFFE0000;
    position->unk_08 = lowered_z - (random_value & 0xFFF);
    next_speed = (u16) ((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34 - 8;
    ((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34 = next_speed;
    if (((next_speed << 0x10) <= 0) || (state->unk_14 & 0x8000)) {
        ((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_00 = (u16) (((S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
