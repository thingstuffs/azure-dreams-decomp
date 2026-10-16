#include "common.h"

extern s32 D_80019AFC;
extern s32 func_8001628C(void);
extern s32 townSelectDataByKindAndIndex(s32, s32, s32);

/* Dispatch the inputs according to the current state. */
s32 townDispatchInputsByCurrentState(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    s32 state = D_80019AFC;

    if (state == 0) {
        return func_8001628C();
    }
    if (state == 2) {
        return townSelectDataByKindAndIndex(input_a, input_b, input_c);
    }
    return 0;
}
