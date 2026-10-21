#include "common.h"

#include "common.h"
#include "engine/resource.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

typedef struct {
    void *data;
    s32 value;
} Entry;

extern s32 fade_manager_state[];
extern s32 runtime_resource_directory[];

/* Processes the selected entry and uploads its two image regions to VRAM. */
s32 activate_indexed_resource_and_upload_images(s32 entry_group, s32 entry_index) {
    s32 *state = fade_manager_state;
    Entry *entries;
    void *entry_data;
    s32 result;

    if (entry_index >= 0) {
        entries = (Entry *)lookup_sentinel_resource_value_or_zero(entry_group);
        if (entries != 0) {
            entry_data = entries[entry_index].data;
            if (entry_data != 0) {
                state[2] = entries[entry_index].value;
                result = find_or_load_runtime_resource_key(entry_data);
                runtime_move_entry_to_front(result);

                LoadImage(resource_directory_upload_rectangles, (void *)runtime_resource_directory[1]);
                LoadImage(&resource_directory_upload_rectangles[2],
                          (void *)(runtime_resource_directory[1] + 0x2000));

                return result;
            }
        }
    }

    return -1;
}
