#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus/data.h"
#include "engine/text.h"

typedef struct S_8004ED00_0_pre {
    void (*unk_00)(void *);
    u8 pad_04[0xC];
} S_8004ED00_0_pre;   /* the 0x10 bytes before arg0 in func_8004ED00, addressed as arg0[-1] */

typedef struct S_8004ED00_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_8004ED00_0;   /* arg0 in func_8004ED00 */
extern s32 gpu_scratch_write_pointer[];

/* Processes flagged state with drawing synchronization and installs the next callback. */
void load_transition_image_and_begin_data_read(void *state) {
    if (((S_8004ED00_0 *)state)->unk_08 != 0) {
        run_image_load_commands(0x80020000, gpu_scratch_write_pointer[0]);
        DrawSync(0);
        scene_begin_transition_data_read(state + 9);
        ((S_8004ED00_0_pre *)state)[-1].unk_00 = &propagate_linked_removal_request;
    }
}
