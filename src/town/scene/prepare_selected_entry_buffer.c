#include "common.h"
#include "town/scene/entry_output.h"
#include "town/scene.h"
#include "town/scene/motion.h"

typedef struct Entry {
    u32 value;
    s32 unused[2];
} Entry;

extern Entry town_selection_records[8];
extern s32 D_80017AAC[3];
extern s32 scene_first_component_values[3];
extern s32 D_80017BD8[13];

// Prepares and returns the shared buffer using the selected entry's value.
s32 *prepare_selected_entry_buffer(s32 entryIndex) {
    s32 *sharedBuffer = D_80017BD8;

    sharedBuffer[8] = town_selection_records[entryIndex].value;
    copy_callback_value_to_destination(sharedBuffer, D_80017AAC);
    copy_callback_value_to_destination(sharedBuffer + 5, scene_first_component_values);
    return sharedBuffer;
}
