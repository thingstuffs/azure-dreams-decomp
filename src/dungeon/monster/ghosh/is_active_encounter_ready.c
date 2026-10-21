#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


extern EntityRec *ghosh_actor_node;

/* Return whether the current record's unk_D2 field is zero. */
s32 is_active_encounter_ready(void) {
    return ghosh_actor_node->unk_D2 == 0;
}
