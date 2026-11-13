#include "shared/position_query.h"
#include "town/scene/collision.h"
#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/object_links.h"
#include "town/scene/flags.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/scene/motion.h"
#include "town.h"
#include "town/event/motion.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/data.h"
#include "town/event.h"
#include "slus.h"

typedef void (*Callback)(void *, void *, void *, s32);


   /* the 0x2 bytes before arg0 in update_motion_and_handle_terrain_contact, addressed as arg0[-1] */

typedef struct S_8009B6B4_2 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8009B6B4_2;   /* arg0 in update_motion_and_handle_terrain_contact */




/* Update object motion, handle contact, and play the tile height sound. */
void update_motion_and_handle_terrain_contact(void *object, Rec_D_800CFCB4 *collision, ObjectPosition *motion, s32 callback_arg) {
    s16 contact_height;
    s32 contact_height_ext;

    add_vertical_gravity(motion);
    if (motion->velocity_z > 0x200000) {
        motion->velocity_z = 0x200000;
    }
    add_motion_deltas_to_position(motion);
    contact_height = get_min_surface_probe_capped(motion, ((u8 *)&position_query_scratch));
    apply_bound_adjustments(collision, motion);
    resolve_collider_overlaps(collision, motion);
    contact_height_ext = contact_height;
    if (motion->z.w.i >= contact_height_ext) {
        stop_at_max_z(collision, motion, contact_height_ext);
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    } else if (collision->unk_3B != 0) {
        motion->velocity_z = 0;
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    }
    if ((((ObjectRetirementFlags *)object)[-1].flags & 0x8000) == 0 &&
        update_actor_surface_motion == ((S_8009B6B4_2 *)object)->unk_50) {
        s32 tile_type;

        tile_type = check_masked_value_in_current_range((u16)read_map_cell_at_world_position(
            motion->x.w.i, motion->y.w.i));
        if (tile_type != 0) {
            s16 *thresholds = terrain_height_limits;
            s16 height = motion->z.w.i;
            s16 threshold = thresholds[tile_type];

            if (height > threshold) {
                SD_Call(0x517);
            }
        }
    }
}
