#include "common.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "engine/resource.h"
#include "shared/entity.h"

typedef struct {
    s32 pad[3];
    s32 first;
    s32 second;
} FuncData;

/* Add a directional step to the vector and scale it down if it exceeds the length limit. */
void add_a_directional_step_vector_scale_down_exceeds_length_limit(s16 angle, s32 max_length, ObjectPosition *vector) {
    s32 first_step;
    s32 second_step;
    s32 length;

    first_step = rsin(angle) << 6;
    second_step = rcos(angle) << 6;
    vector->velocity_x += first_step;
    vector->velocity_y += second_step;
    length = runtime_estimate_vector_length(vector->velocity_x, vector->velocity_y);
    if (max_length < length) {
        vector->velocity_x = vector->velocity_x / ((length + 0xFFF) / 0x1000) * (max_length / 0x1000);
        vector->velocity_y = vector->velocity_y / ((length + 0xFFF) / 0x1000) * (max_length / 0x1000);
    }
}
