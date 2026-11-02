#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

typedef struct S_806D45CC_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_806D45CC_2;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in update_object_entry_flag */


typedef struct S_806D45CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D45CC_0;   /* arg0 in update_object_entry_flag */
void apply_selected_entry_values(void *, s32);             /* extern */

/* Update the object, clear the current entry flag, and forward the call. */
void update_object_entry_flag(S_806D45CC_0 *object, s32 context) {
    set_script_flag_bit(object->unk_18);
    ((S_806D45CC_2 *)(((town_scene_root->entry_index * 8) + ((s32)town_scene_root->event_data))))->unk_04 = 0;
    apply_selected_entry_values(object, context);
}
