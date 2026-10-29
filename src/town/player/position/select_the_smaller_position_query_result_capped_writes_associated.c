#include "common.h"
#include "town/player/coordinates.h"
#include "town/map.h"
#include "town/player/position.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} LocalRecord;
typedef struct { s32 x; s32 y; s32 z; } Vec3i;
typedef struct { s32 x; s32 y; s32 z; s32 pad; } Vec4i;
s16 select_lowest_corrected_probe(Vec3i *origin, Vec4i *items, s32 count, s32 *best_item, s32 best_value, s32 initial_item);
extern Vec4i *town_corrected_probe_samples;
extern s32 town_collision_motion[];

/* Selects the smaller position query result, capped at 64, and writes its associated value. */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *position_data, s32 *out_value) {
    s32 *position;
    LocalRecord local_pos;
    s32 query_value;
    s32 *height_base;
    s32 *query_value_ptr;
    s32 result;
    s16 min_result;
    s16 candidate_result;

    position = position_data;
    height_base = town_collision_motion;
    query_value_ptr = &query_value;
    local_pos.x = position[0];
    local_pos.y = position[1];
    local_pos.z = position[2] - height_base[5];
    min_result = forward_surface_query_with_argument(&local_pos, query_value_ptr);
    *out_value = query_value;
    local_pos.x = position[0];
    local_pos.y = position[1];
    local_pos.z = position[2] - height_base[5];
    candidate_result = select_lowest_corrected_probe(&local_pos, town_corrected_probe_samples, 4, query_value_ptr, min_result, *out_value);
    if (candidate_result < min_result) {
        min_result = candidate_result;
        *out_value = query_value;
    }
    if (min_result >= 64) {
        min_result = 64;
    }
    result = min_result;
    return result;
}

/* MECHANISM: A 24-byte escaping record at sp+0x18 followed by the sibling
   output local at sp+0x30 creates retail's 0x50 frame.  The global height
   base and output-local address remain live across both external calls.
   A kept named return value prevents the final sign extension sinking. */
