#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(s32 *);

extern void func_800A4A58(void);
extern s16 D_8006ADD4;
extern s8 D_800D1554;
extern s32 D_80100D90;
extern s32 D_80100DB8[];
extern s32 D_80100DE0[];

/* Run both contexts' callbacks, then update the flag from the current mode and threshold. */
void func_800A496C(void)
{
    s32 *primary_context;
    s32 *secondary_context;
    Callback callback;

    primary_context = D_80100DE0;
    secondary_context = D_80100DB8;

    callback = FIELD(primary_context, Callback, 0x24);
    if (callback != NULL) {
        callback(primary_context);
    }
    if (FIELD(secondary_context, Callback, 0x1C) != NULL) {
        FIELD(secondary_context, Callback, 0x1C)(secondary_context);
    }
    if (FIELD(primary_context, Callback, 0x28) != NULL) {
        FIELD(primary_context, Callback, 0x28)(primary_context);
    }
    if (FIELD(secondary_context, Callback, 0x20) != NULL) {
        FIELD(secondary_context, Callback, 0x20)(secondary_context);
    }

    func_800A4A58();
    if (D_8006ADD4 != 0xC) {
        if (*(s16 *)(D_80100D90 + 6) < 0x600) {
            D_800D1554 = 1;
            return;
        }
        D_800D1554 = 0;
    }
}

