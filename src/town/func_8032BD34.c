#include "common.h"

extern s32 townGetScriptFlagMask(s32 flagIndex);
extern void townSetIndexedEntryFlag(s32 record, s32 entry_index);

s32 townDispatchIfCondition1463(s32 dispatch_value, s32 dispatch_option) {
    if (townGetScriptFlagMask(0x1463) != 0) {
        townSetIndexedEntryFlag(dispatch_value, dispatch_option);
        return 1;
    }
    return 0;
}
