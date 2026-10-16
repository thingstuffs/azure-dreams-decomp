#include "common.h"

extern s32 townGetScriptFlagMask(s32 flagIndex);
extern void townSetScriptFlagBit(s32 bit_index);
extern void *townApplyEntryPosition(void *entries, void *object, s32 context, s32 selection);

extern u8 D_8001BE24[];
extern u8 D_8001C354[];
extern u8 D_8001DCD4[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

/* Selects an entry pointer, with state-dependent alternatives for entry 0x1E. */
void *townSelectStateDependentEntry(s32 table_index, s32 unused, s32 entry_id) {
    void *result;

    if (entry_id == 0x1E) {
        if (townGetScriptFlagMask(0x145E) != 0) {
            if (townGetScriptFlagMask(0x145F) != 0) {
                result = D_8001E42A;
            } else {
                result = D_8001E16A;
            }
        } else {
            result = D_8001DCD4;
            townSetScriptFlagBit(0x145E);
        }
    } else {
        result = townApplyEntryPosition(D_8001BE24, D_8001C354, table_index, entry_id);
    }
    return result;
}
