#include "common.h"
#include "engine/audio.h"
#include "engine/resource.h"

/* Returns the table entry for a sound ID, or null if it is absent. */
u32 *find_sound_table_entry(s32 sound_id)
{
    s32 index;

    index = find_resource_key_index(sound_id);
    if (index >= 0) {
        return (u32 *)0x800135C4 + index;
    }
    return 0;
}
