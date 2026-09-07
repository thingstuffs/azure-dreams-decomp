#include "common.h"

typedef s32 (*Callback)(s32);

extern void *D_80016000[3];

/* Stores status code 0x15 or 0x13 according to the callback's low result bit. */
s32 func_80018A54(void) {
    register s32 *statusCodePtr;
    s32 statusCode;

    do {
        statusCodePtr = (s32 *)(*(u8 *volatile *)((u8 *)D_80016000[0] + 0x38) + 0x3188);
    } while (0);
    ASM_KEEP(statusCodePtr);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    if ((*(Callback *)(*(u8 **)((u8 *)D_80016000[0] + 0x20) + 0x54))(2) & 1) {
        statusCode = 0x15;
    } else {
        statusCode = 0x13;
    }
    do {
        *statusCodePtr = statusCode;
    } while (0);
    return 1;
}
