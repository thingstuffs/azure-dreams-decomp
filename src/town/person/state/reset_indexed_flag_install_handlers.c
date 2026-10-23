#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "records/Rec_D_80082E80.h"

extern void initialize_object_entries(void *state, s32 output, void *entries);
extern void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
extern s32 person_menu_object_entries[];
extern M2C_UNK D_800D5624;
extern M2C_UNK D_800D562C;
extern M2C_UNK D_800D5654;
extern M2C_UNK D_800D5658;

typedef struct S_800C5C70_1 {
    u8 pad_00[0x58];
    s32 * unk_58;
    s32 * unk_5C;
    s32 unk_60;
    u8 pad_64[0xC];
    s8 unk_70;
    u8 unk_71;
    u8 pad_72[0xA];
    s32 * unk_7C;
    s32 * unk_80;
} S_800C5C70_1;   /* arg0 in reset_indexed_flag_install_handlers */

/* Reset the indexed flag, install handlers, and update the object on input flags 0x6000. */
void reset_indexed_flag_install_handlers(void *object, s32 context, void *input) {
    if (((SpriteFrameState *)input)->flags & 0x6000) {
        initialize_object_entries(object, input, &person_menu_object_entries);
        object_index_slots[((S_800C5C70_1 *)object)->unk_60].unk_00 = 0;
        ((S_800C5C70_1 *)object)->unk_58 = &D_800D5654;
        ((S_800C5C70_1 *)object)->unk_5C = &D_800D5658;
        ((S_800C5C70_1 *)object)->unk_7C = &D_800D5624;
        ((S_800C5C70_1 *)object)->unk_80 = &D_800D562C;
        ((S_800C5C70_1 *)object)->unk_70 = 1;
        ((S_800C5C70_1 *)object)->unk_71 = (u8) (((S_800C5C70_1 *)object)->unk_71 | 1);
        apply_object_setup_and_update(object, context, input);
    }
}
