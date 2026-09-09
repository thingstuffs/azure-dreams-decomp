#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001EB20[];
extern u8 D_8001EC6A[];

/* Select one of two data pointers based on the query for 0xD83. */
void *func_80016A84(void) {
    void *dispatch_result;

    if (func_8001ADE0(0xD83) != 0) {
        dispatch_result = D_8001EC6A;
    } else {
        dispatch_result = D_8001EB20;
    }
    return dispatch_result;
}
