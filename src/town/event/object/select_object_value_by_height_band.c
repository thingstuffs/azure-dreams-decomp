#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity_height_offsets.h"
#include "town/map/position/read_map_cell_at_tile_g01115.h"

extern void set_actor_motion_state(Rec_func_80094268_arg0 *, void *);
extern s32 check_masked_value_in_current_range(s32 value);
extern s16 terrain_height_limits[];

   /* Selects one of three object values using a position-based table difference. */
void select_object_value_by_height_band(Rec_func_80094268_arg0 *object, void *context, EntityRec *position, Rec_D_80082E80 *output)
{
    s32 table_index;
    s16 table_delta;

    set_actor_motion_state(object, context);
    if (object->unk_7C.as_pv == 0) {
        return;
    }

    table_index = check_masked_value_in_current_range(
        read_map_cell_at_world_position(position->x.w.i, position->y.w.i) & 0xFFFF);
    if (table_index != 0) {
        table_delta = ((u16)position->z.w.i) - terrain_height_limits[table_index];
        if (table_delta >= 0x19) {
            if (table_delta < 0x29) {
                ((SpriteFrameState *)output)->source =
                    ((HeightBandValues *)(object->unk_7C.as_pv))->unk_04;
                return;
            }
            ((SpriteFrameState *)output)->source =
                ((HeightBandValues *)(object->unk_7C.as_pv))->unk_08;
            return;
        }
    }

    ((SpriteFrameState *)output)->source = ((HeightBandValues *)(object->unk_7C.as_pv))->unk_00;
}
