#include "common.h"
#include "shared/object_flags.h"

extern void process_indexed_entry_record(s32);
extern s32 D_800CFCA8;

// Processes the current counter value, increments it, and sets completion flags at 128.
void advance_index_and_mark_completion(void *counterPtr) {
    s32 nextCounter;

    process_indexed_entry_record(*(s32 *)counterPtr);
    nextCounter = *(s32 *)counterPtr + 1;
    *(s32 *)counterPtr = nextCounter;
    if (nextCounter >= 0x80) {
        ((u16 *)counterPtr)[-1] |= 0x8000;
        D_800CFCA8 = 0;
        object_flag_block.flags |= 0x8000;
    }
}
