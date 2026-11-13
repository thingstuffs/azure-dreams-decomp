#include "shared/entity_objects.h"
#include "town/menu/indexed_effect_vectors_g00583.h"

/* Copy the global position to the output with an offset on the third component. */
void copy_global_position_output_offset(s32 unused, ObjectPosition *position_out) {
    position_out->x.v = view_reference_entity.x.v;
    position_out->y.v = view_reference_entity.y.v;
    position_out->z.v = view_reference_entity.z.v + town_target_height_offset;
}
