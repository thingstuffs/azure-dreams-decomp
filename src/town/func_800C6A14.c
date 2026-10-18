#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct { char pad0[0x64]; s16 unk64; char pad1[0x0C]; s16 unk72; char pad2[0x02]; s32 *unk78; } Struct800C5724;


typedef struct S_800C4174_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C4174_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in apply_object_setup_and_update */


void initialize_object_entries(Struct800C5724 *state, s8 *output, s32 *entries);
void install_object_handler_and_clear_slot_flag(void *object, s32 update_context, s32 setup_context);


/* Apply setup from the object descriptor and then run the object update. */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context) {
    initialize_object_entries(object, setup_context, ((S_800C4174_1 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_04);
    install_object_handler_and_clear_slot_flag(object, update_context, setup_context);
}
