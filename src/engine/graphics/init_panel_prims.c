#include "common.h"
#include "engine/graphics.h"
#include "slus/data.h"

/* --- gcc 2.7.2 -O2 -fno-expensive-optimizations translation unit --- */

/* Initializes the sub-objects at offsets 0 and 0x18 from shared templates. */
void init_panel_prims(char *object)
{
    char *base = object;
    fill_primitive_pair(base, panel_primary_primitive_template);
    build_tinted_gradient_rect(base + 0x18, panel_primary_primitive_template, panel_gradient_primitive_template);
}
