#include "shared/actor_status_ids.h"
#include "common.h"
#include "engine/entity.h"
#include "dungeon/monster/cyclone.h"


/* Checks object code 0x19, exits on failure, and applies it on success. */
s32 clear_anorexia_if_present(void *object) {
    if ((get_entity_effect_value(object, STATUS_ANOREXIA) << 0x10) != 0) {
        clear_slots_of_type(object, STATUS_ANOREXIA);
        return 1;
    }
    return 0;
}
