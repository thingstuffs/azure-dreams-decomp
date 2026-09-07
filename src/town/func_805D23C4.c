#include "common.h"

extern s32 D_80019AFC;
extern s32 func_8001628C(void);
extern s32 func_8001632C(void);

s32 func_800163C4(void) {
    s32 state = D_80019AFC;

    if (state == 0) {
        return func_8001628C();
    }
    if (state == 2) {
        return func_8001632C();
    }
    return 0;
}
