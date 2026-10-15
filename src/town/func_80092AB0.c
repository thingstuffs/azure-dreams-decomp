#include "modules/town_player_init.h"

/* Synchronizes the mode flag, updates state, and runs the pending callback. */
void func_80090210(void) {
    s32 disabled_flag;
    s32 enabled_flag;
    s32 mode_result; /* MATCH: Keep the merged call result in v0 for the shared stores. */
    u8 *work_state = (u8 *)&D_80083780.x.v;
    TileObject *update_state = &D_80082E80;
    u8 *handler_state = (u8 *)&D_800834B8;
    void (*callback)();

    if (((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_00 != D_8008FFC0) {
        if (func_80033B2C(0x1202) == 0) {
            ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 0;
            disabled_flag = func_80033B2C(0x1202);
            if (disabled_flag != func_80033B2C(0x9D)) {
                mode_result = func_80048D20();
                D_80080A80 = mode_result;
                update_state->unk_028 = mode_result;
            }
        } else {
            ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 1;
            enabled_flag = func_80033B2C(0x1202);
            if (enabled_flag != func_80033B2C(0x9D)) {
                s32 mode_result;
                mode_result = func_80048D40();
                D_80080A80 = mode_result;
                update_state->unk_028 = mode_result;
            }
        }
        if (func_80033B2C(0x1202) != 0) {
            func_80033AA8(0x9D);
        } else {
            func_80033AE8(0x9D);
        }
        func_80094984(D_800D0078, handler_state, update_state);
        func_80099764(handler_state);
        func_80098868(handler_state, work_state, update_state);
        func_80098928(handler_state, work_state, update_state);
        callback = (void (*)())D_800D0438;
        ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_14 = (s32 *)&D_80097D54;
        ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_1A = 0x10;
        if (callback != NULL) {
            callback();
            D_800D0438 = 0;
        }
    }
}
