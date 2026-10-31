#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"

s32 play_sound_if_enabled(s32 query_value);                     /* extern */


/* Reset object state, clear flag 0x10, and invoke the state handlers. */
void begin_throw_carried_object(ActorRecord *object, s32 unusedArg1, s32 unusedArg2, ActorRecord *handlerContext) {
    object->action_id.s = 0x20;
    object->action_phase.s = 0;
    object->unk_8C.word = 0;
    play_sound_if_enabled(0x512);
    object->unk_A0.parts.high = (u16) (object->unk_A0.parts.high & 0xFFEF);
    append_packed_action_record(handlerContext, 0x30, object->action_timer.s, 0);
}
