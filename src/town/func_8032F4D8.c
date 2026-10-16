#include "common.h"

s32 townGetScriptFlagMask();

/* Returns whether every entry in a zero-terminated list passes townGetScriptFlagMask. */
s32 townAllEntriesPassCheck(s16 *values) {
    s16 *valueCursor;

    for (valueCursor = values; *valueCursor != 0; valueCursor++) {
        if (townGetScriptFlagMask(*valueCursor) == 0) {
            break;
        }
    }
    return *valueCursor == 0;
}
