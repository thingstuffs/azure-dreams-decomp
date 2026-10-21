#include "common.h"
#include "engine/audio.h"
#include "engine/resource.h"

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
