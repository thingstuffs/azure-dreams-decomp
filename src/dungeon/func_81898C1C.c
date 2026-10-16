#include "modules/dungeon_ovl_18b8824.h"

void *func_8002441C(s32 object_id, ovl_18b8824_81898C1C_S_8002441C_3 *initial_state) {
    ovl_18b8824_81898C1C_S_8002441C_1 *display;
    ovl_18b8824_81898C1C_S_8002441C_0 *object;
    ovl_18b8824_81898C1C_S_8002441C_2 *state;
    void *result;

    object = func_8003FC64(0x212);
    if (object != 0) {
        object->unk_10 = (void *)dungeonAdvanceTheEntryCountersTriggerCountMilestonesUpdateTarget;
        display = object->unk_0C;
        object->unk_20 = object_id;
        object->unk_24 = 0;
        display->unk_0E = 0x80;
        display->unk_0D = 0x80;
        display->unk_0C = 0x80;
        display->unk_0E = 0xC0;
        func_8003DB94(display, &D_80024E40, 0);
        display->unk_1C = 0x2000;
        display->unk_1E = 0x1000;
        display->unk_12 = 0x7DCF;
        display->unk_14 = (u16)(display->unk_14 | 0xC);
        display->unk_10 = (u16)(display->unk_10 | 0x20);
        display->unk_14 = (u16)(display->unk_14 | 0x100);
        func_8004491C(object, func_80045340);
        state = object->unk_08;
        state->unk_00 = initial_state->unk_00;
        state->unk_04 = initial_state->unk_04;
        state->unk_08 = initial_state->unk_08;
        state->unk_0C = initial_state->unk_0C;
        state->unk_10 = initial_state->unk_10;
        state->unk_14 = initial_state->unk_14;
        result = object;
        return result;
    } else {
        result = 0;
        return result;
    }
}
