#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
typedef struct S_8009803C_0 S_8009803C_0;
void tick_countdown_and_initialize_record(S_8009803C_0 *state, s32 value, s32 mode);
extern M2C_UNK D_800D01A0;


/* Initialize the object, clear the global flag, and invoke the follow-up routine. */
void initialize_object_and_run_follow_up(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D01A0, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &tick_countdown_and_initialize_record;
    object->unk_0A.as_s16 = 0x15;
    clear_entity_record_fields(followUpArg);
}
