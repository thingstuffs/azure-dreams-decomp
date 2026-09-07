#include "common.h"

typedef s32 (*Callback)(void);

typedef struct CallbackTable {
    Callback slot[5];
} CallbackTable;

typedef struct CallbackTables {
    CallbackTable first;
    Callback pad;
    CallbackTable second;
} CallbackTables;

extern s32 func_80401444(void);
extern s32 func_8040153C(void);
extern CallbackTable D_80400054;
extern CallbackTable D_80400068;
extern s32 D_80409500[];

s32 func_804015D8(void)
{
    CallbackTables callbacks;
    Callback *base;
    Callback callback;
    s32 state;
    s32 result;

    callbacks.first = D_80400054;
    callbacks.second = D_80400068;
    result = 0;
    state = D_80409500[0];
    base = callbacks.first.slot;
    if (state == 0) {
        result = func_80401444();
        if (result != 0) {
            callback = base[result];
            result = callback();
        }
    } else if (state == 1) {
        result = func_8040153C();
        if (result != 0) {
            callback = *(Callback *)((u8 *)base + 0x18 + result * 4);
            result = callback();
        }
    }
    return result;
}
