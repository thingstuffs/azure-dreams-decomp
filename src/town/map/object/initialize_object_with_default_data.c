#include "common.h"
#include "town/map/object_setup.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800CFCB4.h"
#include "engine/node.h"
#include "slus.h"
#include "town/map/object.h"

typedef struct S_800BC8D0_1_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BC8D0_1_pre;   /* the 0x10 bytes before arg0 in initialize_object_with_default_data, addressed as arg0[-1] */

extern u8 D_80089634[];
extern u8 D_800BE0D4[];
extern s32 town_object_defaults[];
extern u8 D_800D20F4[];

/* Initializes the object with default data and updates its associated state. */
void initialize_object_with_default_data(void *object, void *init_arg, SpriteFrameState *state)
{
    s32 *defaults;

    state->flags |= 0x1C;
    ((S_800BC8D0_1_pre *)object)[-1].unk_00 = D_800BE0D4;
    ((Rec_D_800CFCB4 *)object)->unk_50 = 0;
    ((Rec_D_800CFCB4 *)object)->unk_48 = D_80089634;
    register_node((u8 *)object - 0x20, project_sprite_chain);

    defaults = town_object_defaults;
    ((Rec_D_800CFCB4 *)object)->unk_A0 = defaults[0];
    ((Rec_D_800CFCB4 *)object)->unk_A4 = defaults[1];
    ((Rec_D_800CFCB4 *)object)->unk_A8 = defaults[2];
    configure_the_set_mode_n_3(object, init_arg, D_800D20F4);
    select_record_entry_and_value(state, defaults[2], 0);
}
