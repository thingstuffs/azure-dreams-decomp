#include "common.h"

#include "common.h"

typedef s32 (*Func8003875CHandler)(u32);

typedef struct {
    u8 pad_00[0x10];
    void (*callback)(void);
    u8 pad_14[0x1E];
    s8 table_group;
    s8 table_entry;
    u32 callback_arg;
} Func8003875CState;

extern u8 D_80110E98[];
extern void func_80038A10(void);

/* Calls the selected handler and schedules the follow-up callback on a nonzero result. */
void func_8003875C(Func8003875CState *state) {
    Func8003875CHandler *group;
    s32 result;

    group = *(Func8003875CHandler **)((u8 *)&D_80110E98 + (state->table_group * 4));
    result = group[state->table_entry](state->callback_arg);
    if (result != 0) {
        state->callback_arg = result;
        state->callback = func_80038A10;
    }
}
