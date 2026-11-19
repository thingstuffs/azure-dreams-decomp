#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "town/event/motion.h"
#include "town/scene/motion.h"
#include "town/menu/indexed_effect_vectors_g00583.h"


/* Initializes the target parameters and updates the owner's state. */
void initialize_target_motion(TownObjectRecord *owner, struct ColliderView *target, ObjectPosition *parameters, void *unused) {
    s32 combinedValue;

    target->enabled = 0;
    combinedValue = view_reference_entity.z.v + town_target_height_offset;
    parameters->velocity_x = 0;
    parameters->velocity_y = 0;
    parameters->velocity_z = 0;
    parameters->z.v = combinedValue;
    resolve_collider_overlaps(target, parameters);
    owner->unk_50.as_pm = update_motion_toward_town_target;
    owner->timer = 4;
}
