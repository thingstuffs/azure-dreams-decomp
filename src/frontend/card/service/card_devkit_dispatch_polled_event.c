#include "common.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card/service.h"

typedef card_dev_event_callback_fn Callback;
typedef card_dev_event_table CallbackTable;

typedef struct CallbackTables {
    CallbackTable first;
    Callback pad;
    CallbackTable second;
} CallbackTables;

extern s32 func_8040153C(void);
extern s32 card_ui_event_mode[];

/* Dispatches a nonzero selection through the callback table for the current state. */
s32 card_devkit_dispatch_polled_event(void)
{
    CallbackTables callbacks;
    Callback *table_base;
    Callback callback;
    s32 state;
    s32 result;

    callbacks.first = D_80400054;
    callbacks.second = D_80400068;
    result = 0;
    state = card_ui_event_mode[0];
    table_base = callbacks.first.slot;
    if (state == 0) {
        result = card_devkit_poll_first_software_event();
        if (result != 0) {
            callback = table_base[result];
            result = callback();
        }
    } else if (state == 1) {
        result = func_8040153C();
        if (result != 0) {
            callback = *(Callback *)((u8 *)table_base + 0x18 + result * 4);
            result = callback();
        }
    }
    return result;
}
