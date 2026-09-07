#include "common.h"

extern void func_80016CC4(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 func_8001A8EC(s32);
extern s8 D_80016000[];

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the object callback when they are met. */
s32 func_80017EF0(void) {
    s8 *callback_owner;
    s32 status;

    func_80016CC4();
    if (func_8001A8EC(0xB) != 0) {
        func_8001A554(0x93B);
    }

    if (func_8001A64C(0x94A) == 0) {
        func_8001A554(0x946);
        return 1;
    }

    if (func_8001A64C(0x946) != 0) {
        goto return_one;
    }

    func_8001A554(0x942);
    callback_owner = *(s8 **)(*(s8 **)D_80016000 + 0x20);
    (*(TownCallback *)(callback_owner + 0x2F8))(0xE, 0x200);
    status = 0;
    goto done;

return_one:
    status = 1;

done:
    return status;
}
