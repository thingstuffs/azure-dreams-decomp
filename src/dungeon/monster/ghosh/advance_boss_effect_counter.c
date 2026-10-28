#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"


typedef struct S_80170CBC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80170CBC_0;

/* Clear the object's halfword field and increment its byte counter. */
void advance_boss_effect_counter(void) {
    ActorRecord *object;
    void *body;

    body = ghosh_scripted_actor + 1;
    object = body;
    object->action_timer.s = 0;
    object->action_id.u = (u8) (object->action_id.u + 1);
}
