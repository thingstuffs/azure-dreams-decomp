#include "common.h"

#include "common.h"

extern s32 runtime_find_sentinel_table_value(s32 value);

/* Returns the table entry for a sound ID, or null if it is absent. */
u32 *find_sound_table_entry(s32 sound_id)
{
    s32 index;

    index = runtime_find_sentinel_table_value(sound_id);
    if (index >= 0) {
        return (u32 *)(0x800135C4 + (index << 2));
    }
    return 0;
}
