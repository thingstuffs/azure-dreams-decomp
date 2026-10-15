#include "modules/dungeon_ovl_19a332c.h"

void func_80024064(void *transition) {
    ovl_19a332c_81982864_StackPair setup_args;
    s16 restore_frames;
    s16 restore_left;
    s16 dim_left;
    s32 state_or_frames;
    s32 result_or_state;
    u8 transition_kind;
    void *transition_data;
    GameWork *levels;
    void *active_state;
    void *source_data;

    levels = &gameWork;
    state_or_frames = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s;
    switch (state_or_frames) {
    case 0:
        setup_args.first = 0x010003A0;
        setup_args.second = 0x400020;
        func_80040490(&D_80027750, &setup_args);
        func_8003F80C(&D_80027C74, 0x7AC0, 1, 2);
        D_80027C94 = 1;
        transition_kind = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_09;
        active_state = (*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x);
        D_800269D0 = 0;
        D_80027C96 = transition_kind;
        source_data = (*(void **)((u8 *)transition + 0));
        ((ovl_19a332c_81982864_S_80024064_2 *)active_state)->unk_F4 = 0;
        D_80027C98 = source_data;
        ((ovl_19a332c_81982864_S_80024064_2 *)active_state)->unk_A8 = (u8) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_08;
        func_800263F0(active_state);
        ((ovl_19a332c_81982864_S_80024064_6 *)((*(void **)((u8 *)((int *)(&D_800814A8)) + 0))))->unk_96 = 0x14;
        ((ovl_19a332c_81982864_S_80024064_7 *)((*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x)))->unk_102 = 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s = (s16) ((u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.s + 1);
    case 1:
        if (!(*((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_04 & 0x80)) {
            break;
        }
        transition_data = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_00;
        result_or_state = func_800244EC(((ovl_19a332c_81982864_S_80024064_3_pre *)transition_data)[-1].unk_00, transition_data);
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0C = result_or_state;
        if (result_or_state == 0) {
            break;
        }
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 = -1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 = 0x20;
        func_800A56E0(0x300);
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 2:
        state_or_frames = 0x10;
        if (D_80027C94 != 0) {
            break;
        }
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A = (s16) state_or_frames;
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 3:
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x80
            - levels->view.unk_091) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A));
        restore_frames = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A;
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x80 - levels->view.unk_090) / restore_frames));
        restore_left = (u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A - 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_1A = restore_left;
        if ((restore_left << 0x10) > 0) {
            break;
        }
        levels->view.unk_091 = 0x80U;
        levels->view.unk_090 = 0x80U;
        result_or_state = ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 4:
        if (*(s16 *)&D_800269F8 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        ((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 = (u16) (((ovl_19a332c_81982864_S_80024064_0_pre *)transition)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    default:
        break;
    }
update_dimming:
    if (((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 < 0) {
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x20
            - levels->view.unk_091) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22));
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x20
            - levels->view.unk_090) / (s16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22));
        dim_left = (u16) ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 - 1;
        ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_22 = dim_left;
        if ((dim_left << 0x10) <= 0) {
            ((ovl_19a332c_81982864_S_80024064_0 *)transition)->unk_20 = 0;
        }
    }
    D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
