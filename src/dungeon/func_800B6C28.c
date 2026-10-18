#include "common.h"
#include "shared/object_flags.h"


/* Mark completion when the referenced object is flagged or the tracked value is zero. */
void retire_effect_when_owner_or_value_ends(void *context)
{
    void *object = *(void **)context;
    if ((*(u16 *)((u8 *)object + 0x1E) & 0x8000) || (*(*(s32 **)((u8 *)context + 4)) == 0)) {
        *(u16 *)((u8 *)context - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
