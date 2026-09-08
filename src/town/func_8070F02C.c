#include "common.h"

extern void func_80016CC4(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 func_8001A8EC(s32);
extern s8 D_80016000[];

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the town callback if they allow it. */
s32 func_8001802C(void) {
    s8 *callback_object;

    func_80016CC4();
    if (func_8001A8EC(0xB) != 0) {
        func_8001A554(0x93B);
    }

    if ((func_8001A64C(0x94A) == 0) ||
        ((func_8001A64C(0x948) != 0) && (func_8001A64C(0x93B) != 0))) {
        func_8001A554(0x947);
        return 1;
    }

    callback_object = *(s8 **)(*(s8 **)D_80016000 + 0x20);
    (*(TownCallback *)(callback_object + 0x2F8))(0xF, 0x200);
    return 0;
}
