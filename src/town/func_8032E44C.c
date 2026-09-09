#include "common.h"

typedef s32 (*Callback)(void *);

extern s8 D_80016000[];

/* Sum callback results for flagged entries in a terminated four-byte entry list. */
s32 func_80018C4C(void *entry, s32 callback_mode) {
    s32 total;
    Callback callback;

    do {
        total = 0;
    } while (0);
    while (((u8 *)entry)[1] != 0) {
        if (((u8 *)entry)[3] & 0x20) {
            if (callback_mode == 0) {
                void *object;

                object = *(void **)D_80016000;
                object = *(void **)((u8 *)object + 0x20);
                callback = *(Callback *)((u8 *)object + 0x50);
            } else {
                void *object;

                object = *(void **)D_80016000;
                object = *(void **)((u8 *)object + 0x20);
                callback = *(Callback *)((u8 *)object + 0x6C);
            }
            total += callback(entry);
        }
        entry += 4;
    }
    return total;
}
