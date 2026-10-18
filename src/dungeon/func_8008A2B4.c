#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

void append_packed_action_record(); /* extern */
s32 play_sound_if_enabled();                     /* extern */


/* Reset object state, clear flag 0x10, and invoke the state handlers. */
void begin_throw_carried_object(Rec_func_8008ACDC_arg0 *object, M2C_UNK unusedArg1, M2C_UNK unusedArg2, M2C_UNK handlerContext) {
    object->unk_9A.as_s8 = 0x20;
    object->unk_9B.as_s8 = 0;
    object->unk_8C.as_s32 = 0;
    play_sound_if_enabled(0x512);
    object->unk_A2 = (u16) (object->unk_A2 & 0xFFEF);
    append_packed_action_record(handlerContext, 0x30, object->unk_96.as_s16, 0);
}
