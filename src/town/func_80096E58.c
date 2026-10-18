#include "common.h"
#include "m2c_compat.h"

void dispatch_sound_by_global_flag();                            /* extern */
void call_the_handler_selects_nonzero_entry(); /* extern */
extern s32 D_80092CD4;
extern M2C_UNK D_800D0140;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in initialize_input_driven_scene_object */

/* Initialize state and set the output pointer to the shared data. */
void initialize_input_driven_scene_object(s32 **outputData, S_800945B8_0 *state, s32 setupValue) {
    dispatch_sound_by_global_flag();
    state->unk_14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(&D_800D0140, outputData, setupValue);
    *outputData = &D_80092CD4;
}
