#include "common.h"

extern s32 townGetScriptFlagMask(s32 flagIndex);
extern u8 D_8001EB20[];
extern u8 D_8001EC6A[];

/* Select one of two data pointers based on the query for 0xD83. */
void *townSelectDataForConditionD83(void) {
    void *dispatch_result;

    if (townGetScriptFlagMask(0xD83) != 0) {
        dispatch_result = D_8001EC6A;
    } else {
        dispatch_result = D_8001EB20;
    }
    return dispatch_result;
}
