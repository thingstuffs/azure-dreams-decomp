#include "common.h"

extern void townSetScriptFlagBit(s16 bit_index);
extern void townClearScriptFlagBit(s16 bit_index);
extern s32 townGetScriptFlagMask(s16 flagIndex);

/* Updates two dependent IDs according to the checked ID's status, then updates the checked ID. */
void townUpdateDependentEntryIds(s16 checked_id, s16 first_id, s16 second_id)
{
    s16 saved_first_id;
    u16 first_id_copy;
    s16 saved_second_id;
    s16 saved_checked_id;

    saved_first_id = first_id;
    saved_second_id = second_id;
    saved_checked_id = checked_id;
    first_id_copy = saved_first_id;

    if (townGetScriptFlagMask(checked_id) != 0) {
        townSetScriptFlagBit(saved_first_id);
        townSetScriptFlagBit(saved_second_id);
    } else {
        townClearScriptFlagBit(first_id_copy);
    }
    townSetScriptFlagBit(saved_checked_id);
}
