#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void *, void *, void *);

extern void *func_8003FD64(s32, void *);
extern s16 func_800C2AE8(void *);
extern u8 D_80083498[];
extern u32 D_800D3950[];
extern u16 D_800D5070[];


typedef struct S_8009D424_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u32 unk_10;
} S_8009D424_0;   /* obj in func_8009D424 */

typedef struct S_8009D424_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009D424_1;   /* part0 in func_8009D424 */

typedef struct S_8009D424_2 {
    u8 pad_00[0x84];
    u16 unk_84;
} S_8009D424_2;   /* part3 in func_8009D424 */

typedef struct S_8009D424_3 {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x22];
    u16 unk_6E;
    s8 unk_70;
    s8 unk_71;
    u16 unk_72;
    u8 pad_74[0x12];
    u16 unk_86;
    u8 pad_88[0xB];
    s8 unk_93;
    s8 unk_94;
    u8 unk_95;
    u8 unk_96;
    u8 pad_97[0x1];
    s32 unk_98;
} S_8009D424_3;   /* write_base in func_8009D424 */

typedef struct S_8009D424_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8009D424_4;   /* part2 in func_8009D424 */

typedef struct S_if_b1_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_if_b1_0;   /* obj in if */

typedef struct S_if_b2_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_if_b2_0;   /* obj in if */

/* Create an object, initialize its position and render state, and invoke its callback. */
s32 func_8009D424(s32 callback_id, s32 angle_index, s32 state_94,
                  u8 state_95, u8 state_96, u8 height_mode, s32 state_48,
                  u16 coord_x, u16 coord_z, s32 state_98)
{
    s32 saved_angle_index;
    void *object;
    void *position;
    void *object_state;
    void *render_data;
    u16 angle;
    void *state;
    u32 color;
    void *callback_render;
    s32 saved_state_48;
    s32 saved_state_98;
    s32 saved_state_94;

    saved_angle_index = angle_index;
    saved_state_94 = state_94;
    object = func_8003FD64(0x136, D_80083498);
    if (object == 0) {
        return 0;
    }
    if ((callback_id & 0xC0000000) == 0xC0000000) {
        ((S_8009D424_0 *)object)->unk_10 = D_800D3950[(u16)callback_id];
    }
    if ((callback_id & 0xC0000000) != 0xC0000000) {
        ((S_8009D424_0 *)object)->unk_10 = callback_id;
    }

    if (callback_id & 1) {
        position = ((S_8009D424_0 *)object)->unk_08;
        render_data = ((S_8009D424_0 *)object)->unk_0C;
    }
    else if (callback_id & 2) {
        position = ((S_if_b1_0 *)object)->unk_08;
        render_data = ((S_if_b1_0 *)object)->unk_0C;
    }
    else if (callback_id & 4) {
        position = ((S_if_b2_0 *)object)->unk_08;
        render_data = ((S_if_b2_0 *)object)->unk_0C;
    }
    else {
        position = ((S_8009D424_0 *)object)->unk_08;
        render_data = ((S_8009D424_0 *)object)->unk_0C;
    }

    ((S_8009D424_1 *)position)->unk_02 = coord_x;
    object_state = (u8 *)object + 0x20;
    ((S_8009D424_1 *)position)->unk_06 = coord_z;

    if (height_mode == 0) {
        ((S_8009D424_1 *)position)->unk_0A = -0x40;
    } else {
        ((S_8009D424_1 *)position)->unk_0A = -0xC0;
    }
    ((S_8009D424_1 *)position)->unk_0A = func_800C2AE8(position);
    if (position != 0) {
        color = 0x808080;
    }
    else {
        color = 0x808080;
    }
    ((S_8009D424_2 *)object_state)->unk_84 = ((S_8009D424_1 *)position)->unk_02;
    if (position != 0) {
        if (render_data != 0) {
            state = object_state;
        }
        else {
            state = object_state;
        }
    } else {
        if (render_data != 0) {
            state = object_state;
        }
        else {
            state = object_state;
        }
    }
    ((S_8009D424_3 *)state)->unk_86 = ((S_8009D424_1 *)position)->unk_06;
    ((S_8009D424_4 *)render_data)->unk_1E = 0x1000;
    ((S_8009D424_4 *)render_data)->unk_1C = 0x1000;
    ((S_8009D424_4 *)render_data)->unk_0C = color;
    angle = D_800D5070[saved_angle_index & 3];
    ((S_8009D424_3 *)state)->unk_94 = saved_state_94;
    ((S_8009D424_3 *)state)->unk_95 = state_95;
    ((S_8009D424_3 *)state)->unk_96 = state_96;
    if (position != 0) {
        if (render_data != 0) {
            saved_state_48 = state_48;
        }
        else {
            saved_state_48 = state_48;
        }
    } else {
        saved_state_48 = state_48;
    }
    ((S_8009D424_3 *)state)->unk_48 = saved_state_48;
    if (position != 0) {
        if (render_data != 0) {
            saved_state_98 = state_98;
        }
        else {
            saved_state_98 = state_98;
        }
    } else {
        saved_state_98 = state_98;
    }
    ((S_8009D424_3 *)state)->unk_93 = 0;
    ((S_8009D424_3 *)state)->unk_70 = 0;
    ((S_8009D424_3 *)state)->unk_71 = 0;
    ((S_8009D424_3 *)state)->unk_72 = angle;
    ((S_8009D424_3 *)state)->unk_6E = angle;
    ((S_8009D424_3 *)state)->unk_98 = saved_state_98;
    if (position != 0) {
        if (render_data != 0) {
            callback_render = render_data;
        }
        else {
            callback_render = render_data;
        }
    } else {
        callback_render = render_data;
    }
    ((Callback)((S_8009D424_0 *)object)->unk_10)(state, position, callback_render);
    return 1;
}
