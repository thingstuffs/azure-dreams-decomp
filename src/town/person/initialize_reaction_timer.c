#include "common.h"
#include "shared/town_object.h"
#include "engine/window.h"
#include "town/person.h"

/* extern */

/* Call func_800C9C94 and store the result of scale_random_by_limit(3) plus one. */
void initialize_reaction_timer(TownObjectRecord *object, s32 param_1, s32 param_2) {
    start_reaction_countdown(object, param_1, param_2);
    object->unk_90 = (s16) (scale_random_by_limit(3) + 1);
}
