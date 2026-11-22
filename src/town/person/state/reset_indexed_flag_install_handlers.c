#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "records/Rec_D_80082E80.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person/state.h"
#include "town/person/object.h"
#include "town/data.h"
extern M2C_UNK D_800D5624;
extern PersonDescriptor D_800D562C;
extern M2C_UNK D_800D5654;
extern TownIndexedHandler D_800D5658[];

/* Reset the indexed flag, install handlers, and update the object on input flags 0x6000. */
void reset_indexed_flag_install_handlers(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *input) {
    if (input->flags & 0x6000) {
        initialize_object_entries(object, input, person_menu_object_entries);
        object_index_slots[object->slot].unk_00 = 0;
        object->state_handlers = &D_800D5654;
        object->indexed_handlers = D_800D5658;
        object->unk_7C.as_pv = &D_800D5624;
        object->descriptor = &D_800D562C;
        object->unk_70 = 1;
        object->unk_71 = (u8) (object->unk_71 | 1);
        apply_object_setup_and_update(object, position, input);
    }
}
