#include "common.h"
#include "shared/town_handler_entries.h"

void dispatch_sound_by_global_flag(void);                            /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h" /* extern */
extern s32 D_80092CD4;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in initialize_input_driven_scene_object */

/* Initialize state and set the output pointer to the shared data. */
void initialize_input_driven_scene_object(s32 **outputData, S_800945B8_0 *state, s32 setupValue) {
    dispatch_sound_by_global_flag();
    state->unk_14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(D_800D0140, (struct Rec_func_80094268_arg0 *)(outputData), (void *)(setupValue));
    *outputData = &D_80092CD4;
}
