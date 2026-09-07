#include "common.h"

typedef void (*TownCallback)(s32, s32);

extern void func_80016CC4(void);
extern s32 func_8001A64C(s32);
extern s8 D_80016000[];
extern s8 D_8001C921[];

s32 func_8001814C(void) {
    void *town;
    void *owner;
    void *callbacks;
    TownCallback callback;

    func_80016CC4();
    if (func_8001A64C(0x939) != 0) {
        return 1;
    }

    town = *(void **)D_80016000;
    owner = *(void **)((s8 *)town + 0x1C);
    *(void **)((s8 *)owner + 0x40) = D_8001C921;

    callbacks = *(void **)((s8 *)town + 0x20);
    callback = *(TownCallback *)((s8 *)callbacks + 0x2F8);
    callback(0xF, 0x200);
    return 0;
}
