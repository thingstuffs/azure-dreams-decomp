#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

extern s32 D_800D64C8[];
extern u8 D_800C9F58[];
extern s8 D_800826B8;


/* Initializes entries from D_800D64C8, clears D_800826B8, and installs D_800C9F58 with count four. */
void initialize_actor_slot_eleven_countdown(TownObjectRecord *actor, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(actor, output, D_800D64C8);
    D_800826B8 = 0;
    actor->handler = D_800C9F58;
    actor->timer.as_s16 = 4;
}
