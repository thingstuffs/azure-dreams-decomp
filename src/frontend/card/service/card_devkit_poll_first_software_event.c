#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern s32 func_8007C9C8(s32 event_handle);

/* Returns 1 through 4 for the first signaled card software event, or 0 if none is signaled. */
s32 card_devkit_poll_first_software_event(void) {
    s32 result;

    result = 0;
    if (func_8007C9C8(D_80409270[0]) != 0) {
        result = 1;
    } else {
        if (func_8007C9C8(D_80409274[0]) != 0) {
            result = 2;
        } else {
            if (func_8007C9C8(D_80409278[0]) != 0) {
                result = 3;
            } else {
                if (func_8007C9C8(D_8040927C[0]) != 0) {
                    result = 4;
                }
            }
        }
    }
    return result;
}
