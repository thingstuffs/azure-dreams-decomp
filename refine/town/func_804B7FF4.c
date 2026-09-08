#include "common.h"

extern void func_8001611C(s32, s32);
extern s32 func_80017D9C(s32, s32);
extern void func_80018854(s32);
extern s32 func_8001894C(s32);
extern s16 D_80018AEA[];

/* Process the object action when flag 0x510 is set, otherwise update flag 0x511. */
s32 func_800167F4(s32 object, s32 context) {
    func_8001611C(object, context);
    if (func_8001894C(0x510) != 0) {
        return func_80017D9C(object, context);
    }
    if (func_8001894C(D_80018AEA[0]) == 0) {
        func_80018854(0x511);
    }
    return 0;
}
