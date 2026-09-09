#include "common.h"

extern s32 D_80019AFC;

extern s32 func_800169B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80016A00(s32 arg0, s32 arg1);
extern s32 func_80016A4C(void);

/* Dispatches to the handler selected by the global mode. */
s32 func_80016AAC(s32 handler_input_a, s32 handler_input_b, s32 handler_input_c, s32 handler_input_d) {
    if (D_80019AFC == 0) {
        return func_800169B4(handler_input_a, handler_input_b, handler_input_c, handler_input_d);
    }
    if (D_80019AFC == 1) {
        return func_80016A00(handler_input_a, handler_input_b);
    }
    if (D_80019AFC == 3) {
        return func_80016A4C();
    }
    return 0;
}
