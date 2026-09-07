#include "common.h"

typedef s32 (*MainCallback)(void);

typedef struct CallbackSet {
    MainCallback value[5];
} CallbackSet;

typedef struct CallbackWork {
    CallbackSet first;
    s32 pad;
    CallbackSet second;
} CallbackWork;

extern s32 func_80021410(void);
extern s32 func_800214FC(void);
extern CallbackSet D_80020034;
extern CallbackSet D_80020048;
extern s32 D_800287E0[];

s32 func_80021594(void)
{
    CallbackWork work;
    MainCallback *callbacks;
    s32 mode;
    s32 result;

    work.first = D_80020034;
    work.second = D_80020048;
    result = 0;
    mode = D_800287E0[0];
    callbacks = work.first.value;
    if (mode == 0) {
        result = func_80021410();
        if (result != 0) {
            result = callbacks[result]();
        }
    } else if (mode == 1) {
        result = func_800214FC();
        if (result != 0) {
            result = (*(MainCallback *)((u8 *)callbacks + (result * 4) + 0x18))();
        }
    }
    return result;
}
