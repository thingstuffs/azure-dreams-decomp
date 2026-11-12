#include "town/player/position_handlers.h"
#include "common.h"
#include "sdk/libc.h"
#include "town/map.h"
#include "town/player.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} Vec3s32;

extern void *town_primary_probe_samples[3];
#include "town/player/probe_offset_data.h"

/* Return the lower probe result, sampling an X offset when the displacement exceeds the limit. */
s32 get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(ObjectPosition *input_pos) {
    Vec3s32 probe_pos;
    s16 initial_result;
    s32 result;
    s32 x_delta;

    probe_pos.x = input_pos->x.v;
    probe_pos.y = input_pos->y.v;
    probe_pos.z = input_pos->z.v;
    initial_result = min_indexed_query((s32)(&probe_pos), town_primary_probe_samples[0], 6);
    x_delta = town_primary_probe_offset;
    if (abs(x_delta) <= 0x140000) {
        return initial_result;
    }
    probe_pos.x = input_pos->x.v - (x_delta / 2);
    result = min_indexed_query((s32)(&probe_pos), town_primary_probe_samples[0], 6);
    if (result < initial_result) {
        return result;
    }
    return initial_result;
}
