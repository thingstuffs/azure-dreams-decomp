#include "shared/position_query.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/scene/motion.h"
#include "dungeon/actor.h"
#include "dungeon/data.h"
#include "town/map.h"
#include "slus.h"

typedef void (*Callback)(void *, void *, void *, s32);

extern void apply_bound_adjustments(void *, void *);
extern s32 read_map_cell_at_world_position(s16, s16);

/* Updates motion, handles ground contact, and checks the tile height limit. */
void update_falling_motion(void *owner, void *actor, void *motion, s32 callback_arg) {
    s16 ground_height;
    s32 ground_height_s32;

    add_vertical_gravity(motion);
    if (*(s32 *)((u8 *)motion + 0x14) > 0x200000) {
        *(s32 *)((u8 *)motion + 0x14) = 0x200000;
    }
    add_motion_deltas_to_position(motion);
    ground_height = get_min_surface_probe_capped(motion, (&position_query_scratch));
    apply_bound_adjustments(actor, motion);
    resolve_collider_overlaps(actor, motion);
    ground_height_s32 = ground_height;
    if (*(s16 *)((u8 *)motion + 0xA) >= ground_height_s32) {
        stop_at_max_z(actor, motion, ground_height_s32);
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    } else if (*((u8 *)actor + 0x3B) != 0) {
        *(s32 *)((u8 *)motion + 0xC) = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    }
    if ((*(u16 *)((u8 *)owner - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)owner + 0x50) == actor_surface_callback_address) {
        s32 tile_type;

        tile_type = check_masked_value_in_current_range((u16)read_map_cell_at_world_position(
            *(s16 *)((u8 *)motion + 2), *(s16 *)((u8 *)motion + 6)));
        if (tile_type != 0) {
            s16 height = *(s16 *)((u8 *)motion + 0xA);
            s16 height_limit = terrain_height_limits[tile_type];

            if (height > height_limit) {
                SD_Call(0x517);
            }
        }
    }
}
