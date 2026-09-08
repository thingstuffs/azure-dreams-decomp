#include "common.h"

#include "common.h"

extern s32 func_8003C5A4(s32 arg0);

/* Returns the table entry for a sound ID, or null if it is absent. */
u32 *func_8003C8E4(s32 sound_id)
{
    s32 index;

    index = func_8003C5A4(sound_id);
    if (index >= 0) {
        return (u32 *)(0x800135C4 + (index << 2));
    }
    return 0;
}
