#include "common.h"

typedef struct TownCallback {
    u8 pad_00[0x218];
    void (*callback)(void *);
} TownCallback;

typedef struct TownRoot {
    u8 pad_00[0x20];
    TownCallback *callback;
} TownRoot;

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void func_8001886C(s32);
extern s8 D_80016000[];
extern s32 D_800190D4;

/* Dispatches state-dependent actions for two IDs, then invokes the town callback. */
void func_8001677C(void)
{
    void *callback_arg;
    TownRoot *town_root;

    if (func_80018964(0x601) != 0) {
        func_800188E4(0x601);
    } else {
        func_8001886C(0x601);
    }

    if (func_80018964(0x1202) != 0) {
        func_800188E4(0x1202);
    } else {
        func_8001886C(0x1202);
    }

    callback_arg = &D_800190D4;
    town_root = *(TownRoot **)D_80016000;
    town_root->callback->callback(callback_arg);
}
