#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"

s32 play_sound_if_enabled(s32 query_value);                     /* extern */


/* Reset object state, clear flag 0x10, and invoke the state handlers. */
void begin_throw_carried_object(Rec_func_8008ACDC_arg0 *object, s32 unusedArg1, s32 unusedArg2, s32 handlerContext) {
    object->unk_9A.as_s8 = 0x20;
    object->unk_9B.as_s8 = 0;
    object->unk_8C.as_s32 = 0;
    play_sound_if_enabled(0x512);
    object->unk_A2 = (u16) (object->unk_A2 & 0xFFEF);
    append_packed_action_record(handlerContext, 0x30, object->unk_96.as_s16, 0);
}
