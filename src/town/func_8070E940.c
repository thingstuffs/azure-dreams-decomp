#include "common.h"

typedef void (*TownCallback)(s32, s32);

typedef struct TownCallbacks {
    u8 pad[0x2F8];
    TownCallback callback;
} TownCallbacks;

typedef struct TownRoot {
    u8 pad[0x20];
    TownCallbacks *callbacks;
} TownRoot;

extern s32 func_80016CC4();
extern s32 func_8001991C();
extern s32 func_80019988();
extern s32 func_8001A5CC();
extern s32 func_8001A64C();
extern TownRoot *D_80016000;

s32 func_80017940(s32 arg0, s32 arg1) {
    TownRoot *root;

    func_80016CC4();
    if (func_8001A64C(0x943) != 0) {
        func_80019988();
        if (func_8001991C(arg0, arg1) != 0) {
            func_8001A5CC(0x943);
            return 1;
        }
    }

    root = D_80016000;
    root->callbacks->callback(0xF, 0x200);
    return 0;
}
