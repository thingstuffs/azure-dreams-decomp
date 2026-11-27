#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"
#include "town/person/state.h"

typedef struct {
    s8 pad0[0x54];
    void *unk54;
    u8 pad58[8];
    s32 unk60;
} Obj;


extern s32 input_flag_object_heading_entries[];

// Process the flagged event, clear the object's indexed flag, and reset its state pointer.
void initialize_object_on_input_flags(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *event) {
    if (event->flags & 0x6000) {
        initialize_object_entries(object, event, input_flag_object_heading_entries);
        object_index_slots[object->slot].motion_id = 0;
        object->handler = dispatch_status_triggered_handler;
    }
}
