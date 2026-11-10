#include "common.h"
#include "engine/effect/resource_transition.h"
#include "m2c_compat.h"

#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "engine/text.h"

extern s32 gpu_scratch_write_pointer[];

/* Processes flagged state with drawing synchronization and installs the next callback. */
void load_transition_image_and_begin_data_read(void *state) {
    ResourceTransitionBody *record = state;
    if (record->image_ready != 0) {
        run_image_load_commands(0x80020000, gpu_scratch_write_pointer[0]);
        DrawSync(0);
        scene_begin_transition_data_read(state + 9);
        ((ObjectNodeHeader *)state - 1)->update_callback = &propagate_linked_removal_request;
    }
}
