#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void initialize_object_entries(void *,s8 *, s32 *);
extern u8 object_index_slots[][8];
extern void advance_object_countdown_and_invoke_handlers(Rec_func_80094268_arg0 *object, s32 handlerContext, s32 handlerData);
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to six. */
void initialize_object_with_six_tick_counter(void *object_arg, s32 unused, void *context) {
    Rec_func_80094268_arg0 *object = object_arg;

    initialize_object_entries(object, context, D_800D6910);
    object_index_slots[object->unk_60][0] = 0;
    object->unk_54 = &advance_object_countdown_and_invoke_handlers;
    object->unk_6C.as_s16 = 6;
}
