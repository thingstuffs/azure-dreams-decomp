#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 town_action_reset_byte;
typedef struct S_800980B4_0 S_800980B4_0;

/* Initialize the object's data and state, then run the setup callback. */
void initialize_object_and_reset_value(Rec_func_80094268_arg0 *object, s32 setupArgument, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0180, object, ptr2);
    object->unk_04.as_pm = &tick_countdown_and_reset_value;
    town_action_reset_byte = 0;
    object->unk_0A.as_s16 = 0x15;
    clear_entity_record_fields((struct EntityRec *)(setupArgument));
    object->unk_10.as_s16 = 0;
}
