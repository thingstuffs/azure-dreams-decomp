#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_event_state.h"


typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

   /* arg0 in func_806D2AB0 */

   /* ptr in func_806D2AB0 */

   /* (offset - index) * 4 + (u8 *)arg0 in func_806D2AB0 */


extern u8 D_80016148[16];
extern u8 D_80016170[16];

/* Returns the entry index for a key, asserting at main.c line 54 if absent. */
s32 find_event_entry_or_assert(s32 *entries, s32 target_key)
{
    s32 *entry;
    s32 entry_index;
    s32 key_or_offset;

    entry_index = 0;
    if (((TownEventEntryValueView *)entries)->unk_08 != 0) {
        entry = entries;
        while (1) {
            key_or_offset = *entry;
            if (key_or_offset == target_key)
                break;
            entry += 7;
            entry_index++;
            if (((TownEventEntryValueView *)entry)->unk_08 == 0)
                break;
        }
        key_or_offset = entry_index * 8;
        if (((TownEventEntryValueView *)((key_or_offset - entry_index) * 4 + (u8 *)entries))->unk_08 != 0) {
            return entry_index;
        }
    }
    ((Callback3)D_80016000->unk_20->callback_168)(
        D_80016148, D_80016170, 0x36);
    ((Callback1)D_80016000->unk_20->callback_174)(1);
    return entry_index;
}
