#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/system.h"

/* Reset object state, clear flag 0x10, and invoke the state handlers. */
void begin_throw_carried_object(ActorRecord *object, ObjectPosition *unused_context, SpriteFrameState *unused_sprite, ActorRecord *actor) {
    object->action_id = 0x20;
    object->action_phase = 0;
    object->unk_8C.word = 0;
    play_sound_if_enabled(0x512);
    object->unk_A0.parts.high = object->unk_A0.parts.high & 0xFFEF;
    append_packed_action_record(actor, 0x30, object->action_timer, 0);
}
