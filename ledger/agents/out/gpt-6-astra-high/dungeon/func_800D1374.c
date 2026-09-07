#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800D6AD4_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D6AD4_6;   /* temp_v0 in func_800D6AD4 */

typedef struct S_800D6AD4_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D6AD4_7;   /* arg0 in func_800D6AD4 */

typedef struct S_800D6AD4_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D6AD4_8;   /* ((S_800D6AD4_6 *)temp_v0)->unk_08 in func_800D6AD4 */

typedef struct S_800D6AD4_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6AD4_9;   /* ((S_800D6AD4_7 *)arg0)->unk_08 in func_800D6AD4 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_800D6804[3];
extern M2C_UNK D_800D68F4[3];

typedef struct S_800D6AD4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D6AD4_0;   /* temp_v0 in func_800D6AD4 */

typedef struct S_800D6AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D6AD4_1;   /* temp_v1 in func_800D6AD4 */

typedef struct S_800D6AD4_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D6AD4_2;   /* temp_v1_2 in func_800D6AD4 */

typedef struct S_800D6AD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D6AD4_3;   /* temp_v1_3 in func_800D6AD4 */

typedef struct S_800D6AD4_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800D6AD4_4;   /* temp_v0_2 in func_800D6AD4 */

typedef struct S_800D6AD4_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_800D6AD4_5;   /* temp_s0 in func_800D6AD4 */

/* Creates an object at an offset from its parent and initializes its motion and state. */
void func_800D6AD4(S_800D6AD4_7 *parent, s32 state_value, s32 x_offset, s32 y_offset, s32 z_offset,
                   s32 motion_scale) {
    s32 saved_z_offset = z_offset;
    s32 saved_motion_scale = motion_scale;
    s32 scaled_motion;
    S_800D6AD4_5 *object_state;
    void *object;
    S_800D6AD4_4 *motion;
    S_800D6AD4_1 *x_position;
    S_800D6AD4_2 *y_position;
    S_800D6AD4_3 *z_position;

    object = func_8003FD64(0x211, parent);
    if (object != 0) {
        ((S_800D6AD4_0 *)object)->unk_10 = D_800D6804;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)object)->unk_08))->unk_02 =
            (u16)((S_800D6AD4_9 *)(parent->unk_08))->unk_02;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)object)->unk_08))->unk_06 =
            (u16)((S_800D6AD4_9 *)(parent->unk_08))->unk_06;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)object)->unk_08))->unk_0A =
            (u16)((S_800D6AD4_9 *)(parent->unk_08))->unk_0A;
        x_position = ((S_800D6AD4_0 *)object)->unk_08;
        x_position->unk_02 =
            (u16)(x_position->unk_02 + x_offset);
        y_position = ((S_800D6AD4_0 *)object)->unk_08;
        y_position->unk_06 =
            (u16)(y_position->unk_06 + y_offset);
        z_position = ((S_800D6AD4_0 *)object)->unk_08;
        scaled_motion = saved_motion_scale << 0x12;
        z_position->unk_0A =
            (u16)(z_position->unk_0A + saved_z_offset);
        motion = ((S_800D6AD4_0 *)object)->unk_08;
        object_state = object + 0x20;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((S_800D6AD4_8 *)(((S_800D6AD4_6 *)object)->unk_08))->unk_14 =
            (s32)(0xFFFA0000 - scaled_motion);
        object_state->unk_32 = 0x14;
        object_state->unk_34 = 0x14;
        func_8004491C(object, D_800D68F4, scaled_motion);
        ((S_800D6AD4_0 *)object)->unk_20 = state_value;
        object_state->unk_08 = state_value;
        ASM_KEEP(saved_z_offset);   /* MATCH pin: retail immediate-load split depends on it */
        ASM_KEEP(saved_motion_scale);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }
}
