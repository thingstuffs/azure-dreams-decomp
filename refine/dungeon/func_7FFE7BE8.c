#include "common.h"

typedef struct S_7FFE7BE8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x1C];
    s32 unk_2C;
    u8 pad_30[0x14];
    void * unk_44;
} S_7FFE7BE8_0;   /* arg0 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFE7BE8_1;   /* temp_a0 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE7BE8_2;   /* temp_v1 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE7BE8_3;   /* arg2 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE7BE8_4;   /* temp_a0_2 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_7FFE7BE8_5;   /* arg1 in func_7FFE7BE8 */



extern void func_70040A18(void *, void *);
extern void func_7003A7C4(void *, void *, s32);
extern s32 D_8004136C;
extern s32 D_800E2BB8;

/* Initialize the object from its source and position, then configure its display state. */
void func_7FFE7BE8(S_7FFE7BE8_0 *object, S_7FFE7BE8_5 *source, S_7FFE7BE8_3 *position)
{
    S_7FFE7BE8_1 *display_flags;
    S_7FFE7BE8_4 *display_state;
    S_7FFE7BE8_2 *object_position;
    s32 source_value;
    u16 flags;

    object->unk_44 = source;
    func_70040A18(object, &D_8004136C);
    display_flags = object->unk_0C;
    display_flags->unk_10 = 0x20;
    display_flags->unk_14 = display_flags->unk_14 | 0xC;
    object_position = object->unk_08;
    object_position->unk_02 = position->unk_02;
    object_position->unk_06 = position->unk_06;
    object_position->unk_0A = position->unk_0A;
    display_state = object->unk_0C;
    display_state->unk_1E = 0x800;
    display_state->unk_1C = 0x800;
    object->unk_2C = source->unk_0C;
    source_value = source->unk_0C;
    flags = display_state->unk_14;
    display_state->unk_12 = 0x7DCF;
    flags |= 0x100;
    display_state->unk_0C = source_value;
    display_state->unk_14 = flags;
    func_7003A7C4(display_state, &D_800E2BB8, 0);
}
