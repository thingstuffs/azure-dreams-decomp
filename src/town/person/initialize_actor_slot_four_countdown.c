#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/data.h"

extern s32 mother_event_object_entries[];
extern u8 D_800C7CF0[];

void initialize_actor_slot_four_countdown(TownObjectRecord *actor, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(actor, output, mother_event_object_entries);
    mother_event_reset_byte = 0;
    actor->handler = D_800C7CF0;
    actor->timer.as_s16 = 16;
}
