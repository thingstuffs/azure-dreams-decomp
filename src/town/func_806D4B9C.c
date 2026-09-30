#include "common.h"

extern s32 func_80016D98(s32);
extern s32 func_800178A8(void *, s32, s32);
extern s32 func_80017904(void *, s32, s32);
extern s32 func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);
extern s32 func_80018868(s32, s32);
extern void func_800188E8(s32, s32, s32);

extern u8 D_80018A0C[16];
extern u8 D_80018B94[16];
extern u8 D_8001B333[];
extern u8 D_8001B3D2[];

/* Selects a response and advances the four-state counter for event 11. */
s32 func_80016B9C(s32 context, s32 unused, s32 event_id)
{
    u8 *event_table;
    s32 result;
    s32 state_index;

    if (event_id == 1) {
        return (s32) D_8001B3D2;
    }

    result = func_80016D98(event_id);
    if (result != 0) {
        return result;
    }

    event_table = D_80018A0C;
    result = func_80017960(event_table, D_80018B94, context, event_id);
    state_index = func_80018868(0x990, 2);

    if (event_id != 0xB) {
        return result;
    }

    func_80018594(0x998);
    if (func_80017904(event_table, context, 0xB) == 0) {
        if (func_8001868C(0x997) == 0) {
            state_index++;
            if (state_index == 4) {
                state_index = 0;
            }
            func_800188E8(0x990, state_index, 2);
        }
    }

    if (func_800178A8(D_80018A0C, context, event_id) == 0) {
        return result;
    }
    return (s32) D_8001B333;
}
