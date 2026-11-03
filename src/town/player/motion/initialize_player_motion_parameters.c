#include "town/player.h"
#include "common.h"
#include "shared/town_object.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"


typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((TownObjectRecord *)arg0)->unk_44 in initialize_player_motion_parameters */


void call_the_handler_selects_nonzero_entry(s32 *entries, TownObjectRecord *record, void *ptr2);



/* Initialize the record from linked data and apply its update parameters. */
void initialize_player_motion_parameters(void *record, ObjectPosition *update_value, SpriteFrameState *sprite) {
    call_the_handler_selects_nonzero_entry(((S_8009A344_1 *)(((TownObjectRecord *)record)->unk_44))->unk_24, record, sprite);
    set_player_travel_timing(record, update_value, sprite);
}
