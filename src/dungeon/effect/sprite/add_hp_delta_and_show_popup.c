#include "common.h"
#include "dungeon/effect/sprite.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/effect/screen.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */
#include "dungeon/actor.h"
#include "dungeon/effect.h"

/* Adds 0x200 to the object's unk_64 and runs callbacks when its mode-2 check returns zero. */
void add_hp_delta_and_show_popup(ActorRecord *object, s32 unused, ActorRecord *record) {
    if (try_trigger_target_record_effect(object, 2, record) == 0) {
        object->hp_delta = object->hp_delta + 0x200;
        cap_pending_actor_value_delta(object);
        create_actor_value_popup(0x8004, object, object->hp_delta, 1);
        apply_clamped_actor_value_delta(object);
    }
}
