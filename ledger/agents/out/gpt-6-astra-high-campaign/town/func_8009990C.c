#include "common.h"

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0c;
    s32 unk10;
} Func8009990CState;

extern s32 func_80096FF4(Func8009990CState *);

/* Process the state when either trailing field is nonzero, otherwise return zero. */
s32 func_8009706C(Func8009990CState *state) {
    if (state->unk0c != 0 || state->unk10 != 0) {
        return func_80096FF4(state);
    }
    return 0;
}
