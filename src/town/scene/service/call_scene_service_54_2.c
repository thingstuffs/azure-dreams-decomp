#include "common.h"
#include "town/scene/service.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Return the result of the town random-number service with a limit of two. */
s32 call_scene_service_54_2(void) {
    return town_scene_root->services->rand_sn(2);
}
