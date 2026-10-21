#include "slus/runtime_directory.h"
#include "shared/runtime_dispatch.h"
#include "slus.h"


/* PS-X EXE payload at VMA 0x80080A6C: 04 00 00 00. */
s32 runtime_directory_entry_count = 4;

/* Return the index of a matching table key, or -1 if absent. */
s32 find_runtime_table_key_index(s32 key)
{
    s32 entry_index;
    s32 result;

    entry_index = 0;
    if (runtime_directory_entry_count > 0) {
        s32 entry_count;
        s32 *entry_key;

        entry_count = runtime_directory_entry_count;
        entry_key = (s32 *)&runtime_resource_directory;
        do {
            if (key == *entry_key) {
                result = entry_index;
                return result;
            }
            entry_index++;
            entry_key += 2;
        } while (entry_index < entry_count);
    }

    result = -1;
    return result;
}


/* Returns the key's index, assigning the last index if lookup fails or is bypassed. */
s32 find_or_load_runtime_resource_key(s32 key)
{
    s32 index;

    if (runtime_dispatch_state.mode == 2 && *(s8 *)0x800DCF4D != -2) {
        index = -1;
    } else {
        index = find_runtime_table_key_index(key);
    }

    if (index == -1) {
        bind_and_load_indexed_resource_record(key, runtime_directory_entry_count - 1);
        index = runtime_directory_entry_count - 1;
    }

    return index;
}


/* Initializes runtime state and selects its mode from the configuration byte. */
void initialize_runtime_resource_directory(void)
{
    GpTablePrefix default_state;

    __builtin_memcpy(&default_state, &runtime_directory_defaults, 0x20);
    if (runtime_dispatch_state.mode != 2) {
        runtime_resource_directory = runtime_directory_defaults;
        runtime_directory_entry_count = 4;
    } else {
        runtime_resource_directory.value[0] = 0;
        runtime_resource_directory.value[1] = (u32)D_80016000;
        runtime_directory_entry_count = 1;
    }
}
