#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state_updates.h"
#include "town/person/state.h"
extern s32 D_800D54C4[];

/* Process the object when either of its 0x6000 flag bits is set. */
void reset_object_entries_on_flag_bits(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    if (sprite->flags & 0x6000) {
        initialize_object_entries(object, sprite, D_800D54C4);
        clear_record_indexed_byte(object, position, sprite);
    }
}
