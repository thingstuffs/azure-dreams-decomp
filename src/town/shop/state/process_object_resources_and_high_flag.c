#include "common.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

extern void release_null_terminated_entries(void *a0);
extern void flag_object_for_removal(void *a0);
extern void func_800B5020(void *a0);

// Process an object's associated resources and set its and the global high-bit flags.
void process_object_resources_and_high_flag(u8 *object)
{
    u8 *resourceFields;
    u16 objectFlags;
    s32 globalFlags;

    if (object != NULL) {
        resourceFields = object + 0x20;
        release_null_terminated_entries(object + 0x80);
        flag_object_for_removal(*(void **)(resourceFields + 0x20));
        func_800B5020(*(void **)(resourceFields + 0x5C));
        objectFlags = *(u16 *)(object + 0x1E) | 0x8000;
        globalFlags = object_flag_block.flags | 0x8000;
        *(u16 *)(object + 0x1E) = objectFlags;
        object_flag_block.flags = globalFlags;
    }
}
