#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "slus.h"
#include "town/player.h"
#include "town/data.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "shared/sprite_frame_state.h"
extern void D_80091AF0(void *state, void *object, s32 context);

/* Initialize the record with its handler and a count of twelve. */
void initialize_timed_scene_action(TownObjectRecord *record, ObjectPosition *unused_position, SpriteFrameState *setup_value) {
    SD_Call(0x510);
    call_the_handler_selects_nonzero_entry(&timed_scene_handler_entries, record, setup_value);
    record->unk_00 = &D_80091AF0;
    record->unk_0A = 0xC;
}
