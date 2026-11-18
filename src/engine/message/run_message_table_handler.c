#include "common.h"
#include "engine/message.h"


typedef s32 (*Func8003875CHandler)(u32);

struct Func8003875CState {
    u8 pad_00[0x10];
    void (*callback)(struct Func80038A10State *);
    u8 pad_14[0x1E];
    s8 table_group;
    s8 table_entry;
    u32 callback_arg;
};

extern u8 D_80110E98[];

/* Calls the selected handler and schedules the follow-up callback on a nonzero result. */
void run_message_table_handler(Func8003875CState *state) {
    Func8003875CHandler *group;
    s32 result;

    group = *(Func8003875CHandler **)((u8 *)&D_80110E98 + (state->table_group * 4));
    result = group[state->table_entry](state->callback_arg);
    if (result != 0) {
        state->callback_arg = result;
        state->callback = update_message_window;
    }
}
