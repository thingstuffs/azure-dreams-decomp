#include "modules/dungeon_ovl_18c4828.h"

s32 func_800246D0(s32 object_param, Row_818A4ED0_S_818A4ED0_3 *spawn_position) {
    s32 rotation_rng;
    Row_818A4ED0_S_818A4ED0_1 *render_state;
    Row_818A4ED0_S_818A4ED0_2 *position;
    Row_818A4ED0_S_818A4ED0_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = func_80024674;
        object->unk_20 = object_param;
        render_state = object->unk_0C;
        render_state->unk_08 = D_80025214;
        render_state->unk_12 = 0x7E07;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x10C);
        rotation_rng = rand();
        render_state->unk_1A = (s16) (rotation_rng % 0x1000);
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        func_8004491C(object, func_80045340);
        position = object->unk_08;
        {
            s32 unused_rng;
            unused_rng = rand();
        }
        position->unk_02 = (u16) spawn_position->unk_02;
        position->unk_06 = (u16) spawn_position->unk_06;
        {
            u16 final_z = spawn_position->unk_0A;
            position->unk_0A = final_z;
            return (s32)object;
        }
    }
    {
        s32 failure_result;
        failure_result = 0;
        return failure_result;
    }
}
