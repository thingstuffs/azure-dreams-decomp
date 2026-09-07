#include "common.h"

extern s32 func_80176F2C(void *arg0);
extern s32 func_80176F10(void);
extern s32 func_80177E6C(s32 arg0, void *arg1);
extern s32 func_80063734(s32 arg0);

/* Polls for a result and switches buffers when the result is negative. */
s32 func_80040690(void *buffer_state) {
    s32 result;
    s32 buffer_index;
    s32 polls_left;

    polls_left = 0x800000;
    while (1) {
        result = func_80176F2C(buffer_state);
        if (result != 0) {
            break;
        }
        if (--polls_left == 0) {
            return (func_80176F10(), 0);
        }
    }
    if (result > 0) {
        return 0;
    }
    buffer_index = *((s32 *)buffer_state + 2) == 0;
    *((s32 *)buffer_state + 2) = buffer_index;
    func_80177E6C(result, *((void **)buffer_state + buffer_index));
    func_80063734(result);
    return (func_80176F10(), 1);
}
