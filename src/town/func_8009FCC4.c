#include "modules/town_town_windows.h"

/* Create an object, initialize its position and render state, and invoke its callback. */
s32 func_8009D424(s32 callback_id, s32 angle_index, s32 state_94, u8 state_95, u8 state_96, u8 height_mode, s32 state_48, s16 coord_x, s16 coord_z, s32 state_98)
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
    object = func_8003FD64(0x136, ((u8 *)(&D_80083498)));
    if (object == 0) {
        return 0;
    }
    if ((callback_id & 0xC0000000) == 0xC0000000) {
        ((func_8009FCC4_S_8009D424_0 *)object)->unk_10 = D_800D3950[(u16)callback_id];
    }
    if ((callback_id & 0xC0000000) != 0xC0000000) {
        ((func_8009FCC4_S_8009D424_0 *)object)->unk_10 = callback_id;
    }

    if (callback_id & 1) {
        position = ((func_8009FCC4_S_8009D424_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_8009D424_0 *)object)->unk_0C;
    }
    else if (callback_id & 2) {
        position = ((func_8009FCC4_S_if_b1_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_if_b1_0 *)object)->unk_0C;
    }
    else if (callback_id & 4) {
        position = ((func_8009FCC4_S_if_b2_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_if_b2_0 *)object)->unk_0C;
    }
    else {
        position = ((func_8009FCC4_S_8009D424_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_8009D424_0 *)object)->unk_0C;
    }

    ((func_8009FCC4_S_8009D424_1 *)position)->unk_02 = coord_x;
    object_state = (u8 *)object + 0x20;
    ((func_8009FCC4_S_8009D424_1 *)position)->unk_06 = coord_z;

    if (height_mode == 0) {
        ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = -0x40;
    } else {
        ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = -0xC0;
    }
    ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = func_800C2AE8(position);
    if (position != 0) {
        color = 0x808080;
    }
    else {
        color = 0x808080;
    }
    ((func_8009FCC4_S_8009D424_2 *)object_state)->unk_84 = ((func_8009FCC4_S_8009D424_1 *)position)->unk_02;
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
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_86 = ((func_8009FCC4_S_8009D424_1 *)position)->unk_06;
    ((func_8009FCC4_S_8009D424_4 *)render_data)->unk_1E = 0x1000;
    ((func_8009FCC4_S_8009D424_4 *)render_data)->unk_1C = 0x1000;
    ((func_8009FCC4_S_8009D424_4 *)render_data)->unk_0C = color;
    angle = D_800D5070[saved_angle_index & 3];
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_94 = saved_state_94;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_95 = state_95;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_96 = state_96;
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
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_48 = saved_state_48;
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
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_93 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_70 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_71 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_72 = angle;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_6E = angle;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_98 = saved_state_98;
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
    ((func_8009FCC4_Callback)((func_8009FCC4_S_8009D424_0 *)object)->unk_10)(state, position, callback_render);
    return 1;
}
