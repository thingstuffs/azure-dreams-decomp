#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "sdk/libgte_matrix.h"

/* Add three record increments to the corresponding 16-bit components. */
void add_entity_position_to_menu_vector(SVECTOR *components, Fixed1616 increments[3]) {
    components->vx += increments[0].w.i;
    components->vy += increments[1].w.i;
    components->vz += increments[2].w.i;
}
