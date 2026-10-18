#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
typedef struct S_800980B4_0 S_800980B4_0;
void tick_countdown_and_reset_value(S_800980B4_0 *state, s32 value, s32 mode);
extern M2C_UNK D_800D0180;


/* Initialize the object's data and state, then run the setup callback. */
void initialize_object_and_reset_value(Rec_func_80094268_arg0 *object, s32 setupArgument, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0180, object, ptr2);
    object->unk_04.as_pm = &tick_countdown_and_reset_value;
    D_80082668 = 0;
    object->unk_0A.as_s16 = 0x15;
    clear_entity_record_fields(setupArgument);
    object->unk_10.as_s16 = 0;
}
