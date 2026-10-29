#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 town_action_reset_byte;
extern void D_80098180();


/* Initializes an object with default state and clears the shared flag. */
void initialize_object_with_countdown_400(Rec_func_80094268_arg0 *object, s32 setupParameter, s32 initializationParameter) {
    clear_entity_record_fields((struct EntityRec *)(setupParameter));
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, object, (void *)(initializationParameter));
    town_action_reset_byte = 0;
    object->unk_04.as_pm = &D_80098180;
    object->unk_0A.as_s16 = 0x10;
    object->unk_10.as_s16 = 0x400;
}
