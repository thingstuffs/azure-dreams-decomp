#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void initialize_object_entries(void *, s32, s32 *);
extern u8 D_80082660[][8];
extern void advance_object_countdown_and_invoke_handlers(Rec_func_80094268_arg0 *object, s32 handlerContext, s32 handlerData);
extern M2C_UNK D_800D6910;


/* Initialize the object's state, clear its slot flag, and set its counter to six. */
void initialize_object_with_six_tick_counter(void *object, s32 unused, s32 context) {
    initialize_object_entries(object, context, &D_800D6910);
    D_80082660[((Rec_func_80094268_arg0 *)object)->unk_60][0] = 0;
    ((Rec_func_80094268_arg0 *)object)->unk_54 = &advance_object_countdown_and_invoke_handlers;
    ((Rec_func_80094268_arg0 *)object)->unk_6C.as_s16 = 6;
}
