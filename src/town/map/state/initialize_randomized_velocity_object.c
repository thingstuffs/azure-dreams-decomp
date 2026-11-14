#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "engine/window.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/map.h"

struct TownPositionXY; void write_map_mod_square(s16, s16, s16, s16, struct TownPositionXY *);




/* Initialize object tables, settings, and randomized state. */
void initialize_randomized_velocity_object(TownObjectRecord *object, ObjectPosition *random_state, SpriteFrameState *settings) {
    NODE_HEADER(object)->update_callback = run_prop_callback_or_retire;
    object->unk_50.as_pm = adjust_record_fields;
    settings->scale_x = 0x37;
    settings->scale_y = 0x37;
    settings->offset_x = 0xFF00;
    ((Fixed1616 *)&random_state->velocity_x)->w.i = scale_random_by_limit(0xFFFF);
    ((Fixed1616 *)&random_state->velocity_y)->w.i = scale_random_by_limit(0xFFFF);
    ((Fixed1616 *)&random_state->velocity_z)->w.i = scale_random_by_limit(0xFFFF);
    register_node_if_unregistered(object, draw_linked_shaded_quad_rings);
    write_map_mod_square(0x10, 0x11, 0x12, 0x13, (struct TownPositionXY *)random_state);
}
