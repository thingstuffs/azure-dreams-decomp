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
void initialize_target_motion(Rec_func_8009B828_arg0 *owner, Rec_D_800CFCB4 *target, EntityRec *parameters, void *unused) {
    s32 combinedValue;

    target->unk_15 = 0;
    combinedValue = view_reference_entity.z.v + town_target_height_offset;
    parameters->unk_0C = 0;
    parameters->unk_10 = 0;
    parameters->flags14 = 0;
    parameters->z.v = combinedValue;
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(target, parameters);
    owner->unk_50 = update_motion_toward_town_target;
    owner->unk_6C.as_s16 = 4;
}
