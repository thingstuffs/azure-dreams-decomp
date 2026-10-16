#include "common.h"

extern s32 townApplySelectedEntryValues(void *, s32);
extern void townSetScriptFlagBit(s32);
extern void townClearScriptFlagBit(s32);

/* Select the handler for 0xDB8 based on the query result and return its truth value. */
s32 townSelectDB8Handler(void *object, s32 query_value) {
    s32 result;

    if (townApplySelectedEntryValues(object, query_value) == 0) {
        townSetScriptFlagBit(0xDB8);
        result = 0;
    } else {
        townClearScriptFlagBit(0xDB8);
        result = 1;
    }
    return result;
}
