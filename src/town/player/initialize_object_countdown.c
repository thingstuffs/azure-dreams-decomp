#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 town_action_reset_byte;
typedef struct S_80097EC0_0 S_80097EC0_0;
extern s32 D_800D0178;


/* Initializes the object with default data and resets its state. */
void initialize_object_with_countdown_24(Rec_func_80094268_arg0 *object, s32 preparationValue, s32 initializationValue) {
    clear_entity_record_fields((struct EntityRec *)(preparationValue));
    call_the_handler_selects_nonzero_entry(&D_800D0178, object, (void *)(initializationValue));
    object->unk_04.as_pm = &tick_countdown_and_initialize_object;
    town_action_reset_byte = 0;
    object->unk_0A.as_s16 = 0x18;
}
