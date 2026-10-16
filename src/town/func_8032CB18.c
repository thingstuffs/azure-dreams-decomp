#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
s32 townApplySelectedEntryValues();
s32 townProcessCheckedEntry();
void townSetScriptFlagBit();
s32 townGetScriptFlagMask();
/* Update the context flag and dispatch the selected entry according to active flags. */
void townDispatchEntryForActiveFlags(void *context, s32 entry_index)
{
    if (townGetScriptFlagMask(0x1459) != 0) {
        townSetScriptFlagBit(*((s16 *) (((s8 *) context) + 0x18)));
        townProcessCheckedEntry(context, entry_index);
        return;
    }
    if (townGetScriptFlagMask(0x1458) != 0) {
        townSetScriptFlagBit(*((s16 *) (((s8 *) context) + 0x18)));
    }
    townApplySelectedEntryValues(context, entry_index);
}
