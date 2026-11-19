#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "town/map/position/read_map_cell_at_tile_g01115.h"
#include "town/event/object.h"
#include "town/event/motion.h"
#include "town/map.h"
#include "town/data.h"

/* Selects one of three object values using a position-based table difference. */
void select_object_value_by_height_band(TownObjectRecord *object, void *context, ObjectPosition *position, SpriteFrameState *output)
{
    s32 table_index;
    s16 table_delta;

    set_actor_motion_state(object, context, position, output);
    if (object->unk_7C.as_pps32 == 0) {
        return;
    }

    table_index = check_masked_value_in_current_range(
        read_map_cell_at_world_position(position->x.w.i, position->y.w.i) & 0xFFFF);
    if (table_index != 0) {
        table_delta = ((u16)position->z.w.i) - terrain_height_limits[table_index];
        if (table_delta >= 0x19) {
            if (table_delta < 0x29) {
                output->source =
                    object->unk_7C.as_pps32[1];
                return;
            }
            output->source =
                object->unk_7C.as_pps32[2];
            return;
        }
    }

    output->source = object->unk_7C.as_pps32[0];
}
