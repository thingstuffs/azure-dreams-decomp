#include "common.h"
#include "shared/object_flags.h"


/* Subtracts the limit when available, otherwise marks the record and global flags. */
void subtract_limit_or_flag_record(void *record) {
    s32 current = *(s32 *)((s8 *)record + 0x18);
    s32 limit = *(s32 *)((s8 *)record + 0x1C);

    if (current >= limit) {
        *(s32 *)((s8 *)record + 0x18) = current - limit;
        return;
    }
    *(u16 *)((s8 *)record - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
