#include "common.h"
#include "m2c_compat.h"
#include "town/minigame/entry_state.h"
#include "town/minigame.h"
#include "shared/entity.h"
#include "shared/minigame_body.h"



typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} WaypointBounds;


extern WaypointBounds D_800240F0[14];


/* Advance the entry index when the point is inside its bounds, counting completed cycles. */
void advance_path_waypoint(ObjectPosition *bounds_data, MinigameProgressPair16 *progress) {
    s16 next_index;
    s16 entry_y;
    s16 entry_x;
    s16 point_x;
    s32 point_y;
    WaypointBounds *entry;

    point_x = bounds_data->x.w.i;
    point_y = bounds_data->y.w.i;
    entry = D_800240F0;
    entry += progress->checkpoint_index;
    entry_x = entry->x;
    if ((point_x >= entry_x) &&
        ((entry_x + entry->width) >= point_x)) {
        entry_y = entry->y;
        if (point_y >= entry_y && (entry_y + entry->height) >= point_y) {
            next_index = (u16)progress->checkpoint_index + 1;
            progress->checkpoint_index = next_index;
            if (next_index >= 0xE) {
                progress->checkpoint_index = 0;
                progress->lap_count = (u16)(progress->lap_count + 1);
            }
        }
    }
}
