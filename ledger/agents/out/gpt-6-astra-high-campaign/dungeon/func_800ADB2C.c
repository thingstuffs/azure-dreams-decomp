#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B328C_0_pre {
    u16 unk_00;
} S_800B328C_0_pre;   /* the 0x2 bytes before arg0 in func_800B328C, addressed as arg0[-1] */

typedef struct S_800B328C_0 {
    void * unk_00;
    s32 unk_04;
    u8 pad_08[0x84];
    s16 unk_8C;
    u16 unk_8E;
} S_800B328C_0;   /* arg0 in func_800B328C */

typedef struct S_800B328C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B328C_1;   /* temp_a1 in func_800B328C */

typedef struct S_800B328C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B328C_2;   /* arg1 in func_800B328C */

typedef struct S_800B328C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B328C_3;   /* temp_a0 in func_800B328C */

typedef struct S_800B328C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B328C_4;   /* ((S_800B328C_0 *)arg0)->unk_00 in func_800B328C */


s32 func_8003DE58();     /* extern */
M2C_UNK func_800B8EA8(); /* extern */
extern M2C_UNK D_800814A0;

/* Update the position from a base and offset, and mark completion or timeout. */
void func_800B328C(void *state, void *position) {
    u16 offset[3];
    u16 new_position[3];
    s16 old_x;
    s16 old_y;
    s32 old_z_shifted;
    u16 new_x;
    u16 new_y;
    u16 new_z;
    u16 ticks_left;
    void *base_position;
    void *offset_source;

    offset_source = ((S_800B328C_4 *)(((S_800B328C_0 *)state)->unk_00))->unk_0C;
    if (func_8003DE58(((S_800B328C_1 *)offset_source)->unk_08, offset_source, offset, 0) != 0) {
        base_position = ((S_800B328C_4 *)(((S_800B328C_0 *)state)->unk_00))->unk_08;
        if (((S_800B328C_0 *)state)->unk_8C != 0) {
            old_x = (s16) ((S_800B328C_2 *)position)->unk_02;
            old_y = (s16) ((S_800B328C_2 *)position)->unk_06;
            old_z_shifted = ((S_800B328C_2 *)position)->unk_0A << 0x10;
            new_x = ((S_800B328C_3 *)base_position)->unk_02 + offset[0];
            ((S_800B328C_2 *)position)->unk_02 = new_x;
            new_position[0] = new_x;
            new_y = ((S_800B328C_3 *)base_position)->unk_06 + offset[1];
            ((S_800B328C_2 *)position)->unk_06 = new_y;
            new_position[1] = new_y;
            new_z = ((S_800B328C_3 *)base_position)->unk_0A + offset[2];
            ((S_800B328C_2 *)position)->unk_0A = new_z;
            new_position[2] = new_z;
            func_800B8EA8(((S_800B328C_0 *)state)->unk_00, old_x, old_y, old_z_shifted >> 0x10, new_position, ((S_800B328C_0 *)state)->unk_04, 2, 0x800, 1);
        } else {
            ((S_800B328C_2 *)position)->unk_02 = (u16) (((S_800B328C_3 *)base_position)->unk_02 + offset[0]);
            ((S_800B328C_2 *)position)->unk_06 = (u16) (((S_800B328C_3 *)base_position)->unk_06 + offset[1]);
            ((S_800B328C_2 *)position)->unk_0A = (u16) (((S_800B328C_3 *)base_position)->unk_0A + offset[2]);
            ((S_800B328C_0 *)state)->unk_8C = 1;
        }
    } else if (((S_800B328C_0 *)state)->unk_8C != 0) {
        goto mark_finished;
    }
    if (ticks_left = ((S_800B328C_0 *)state)->unk_8E - 1, ((S_800B328C_0 *)state)->unk_8E = ticks_left, ((s16) ticks_left < 0)) {
mark_finished:
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800B328C_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
