#include "common.h"

extern s32 func_80016250(s32);
extern void func_80018570(void);
extern s32 D_8001967C;
extern s32 D_8001970C[];

/* Processes the selected entry for event eight, then runs the completion callback. */
s32 func_80016A4C(s32 unused_context, s32 unused_arg, s32 event_kind) {
    s32 result = 0;

    if (event_kind == 8) {
        result = func_80016250(D_8001970C[D_8001967C]);
    }
    func_80018570();
    return result;
}
