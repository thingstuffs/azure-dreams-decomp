#include "engine/resource/konami_runtime_gp_count.h"

#include "engine/resource/konami_runtime_gp_count.h"
#include "engine/resource.h"

/* Binds data and its paired pointer from the resource directory, then loads the indexed record. */
void bind_and_load_indexed_resource_record(void *data, s32 entry_index)
{
    Func8003C6F8Entry *entry;
    Func8003C6F8Entry *entries;
    void *paired_data;

    entries = runtime_resource_directory;
    entry_index *= 8;
    entry = (Func8003C6F8Entry *)((u8 *)entries + entry_index);
    paired_data = entry->field_4;
    entry->field_0 = data;
    runtime_resource_load_target = data;
    *(void **)0x80080A8C = paired_data;
    file_load_com(data);

    if (runtime_dispatch_state.mode == 2) {
        *(s8 *)0x800DCF4D = -2;
    }
}
void *runtime_resource_load_target = 0;
