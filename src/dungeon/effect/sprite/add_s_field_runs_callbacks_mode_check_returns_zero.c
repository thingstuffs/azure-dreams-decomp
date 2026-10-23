#include "common.h"
#include "dungeon/effect/sprite.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/effect/screen.h"                 /* extern */
void apply_clamped_actor_value_delta();                      /* extern */
s16 cap_pending_actor_value_delta();                      /* extern */
void *create_actor_value_popup(); /* extern */


/* Adds 0x200 to the object's unk_64 and runs callbacks when its mode-2 check returns zero. */
void add_hex_200_s_field_64_runs_callbacks_mode_n_2_check_returns_zero(EntityRec *object, s32 unused, void *record) {
    if (try_trigger_target_record_effect(object, 2, record) == 0) {
        object->unk_64 = (u16) (((u16)object->unk_64) + 0x200);
        cap_pending_actor_value_delta(object);
        create_actor_value_popup(0x8004, object, (s16) ((u16)object->unk_64), 1);
        apply_clamped_actor_value_delta(object);
    }
}
