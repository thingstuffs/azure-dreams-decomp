#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C70B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C70B8_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in clear_table_flag_and_reset_animation */


extern void initialize_object_entries();
extern void apply_object_setup_and_update();


/* Clears the object's table flag and resets its animation before updating it. */
void clear_table_flag_and_reset_animation(Rec_func_80094268_arg0 *object, s32 position, s32 anim_state) {
    initialize_object_entries(object, anim_state, ((S_800C70B8_1 *)(object->unk_80))->unk_04);
    *(((u8 *)object_index_slots) + (object->unk_60 * 8)) = 0;
    object->unk_72.as_s16 = 0x200;
    apply_object_setup_and_update(object, position, anim_state);
}
