#include "common.h"

typedef s32 (*Callback)(s32);

extern void *D_80016000[3];

/* Stores status code 0x15 or 0x13 according to the callback low result bit. */
s32 func_80018A54(void) {
    s32 *statusCodePtr;
    s32 statusCode;

    statusCodePtr = (s32 *)(*(u8 **)((u8 *)D_80016000[0] + 0x38) + 0x3188);
    if ((*(Callback *)(*(u8 **)((u8 *)D_80016000[0] + 0x20) + 0x54))(2) & 1) {
        statusCode = 0x15;
    } else {
        statusCode = 0x13;
    }
    *statusCodePtr = statusCode;
    return 1;
}
