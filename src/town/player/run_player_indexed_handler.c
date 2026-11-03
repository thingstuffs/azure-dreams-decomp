#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/player.h"
#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"


   /* call_arg0 in run_player_indexed_handler */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((TownObjectRecord *)arg0)->unk_44 in run_player_indexed_handler */


extern s32 call_the_handler_selects_nonzero_entry();

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void run_player_indexed_handler(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    call_the_handler_selects_nonzero_entry(((S_8009A3A4_2 *)(object->unk_44))->unk_14, object, sprite);
    *(((u8 *)object_index_slots) + (object->unk_40 * 8)) = 0;
    initialize_record_with_handler_table(object, position, sprite);
}
