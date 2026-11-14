#include "engine/camera/interpolation.h"
#include "shared/game_work.h"
#include "common.h"
#include "m2c_compat.h"

#include "engine/util.h"




/* Advances a three-component interpolation and deactivates it when complete. */
void advance_camera_interpolation(CameraInterpolationBody *record_data) {
    s32 progress;
    u16 delta_x;
    u16 delta_y;
    u16 delta_z;
    s16 *output;

    output = record_data->output;
    progress = record_data->progress + record_data->step;
    record_data->progress = progress;
    if (progress >= 0x1000) {
        record_data->progress = 0x1000;
        ((ViewSlot *)((u8 *)record_data - 4))->callback = 0;
    }
    delta_x = record_data->delta[0].u;
    output[0] = (s16) ((record_data->target[0] - delta_x)
        + ((s32) ((s16) delta_x * record_data->progress) >> 0xC));
    delta_y = record_data->delta[1].u;
    output[1] = (s16) ((record_data->target[1] - delta_y)
        + ((s32) ((s16) delta_y * record_data->progress) >> 0xC));
    delta_z = record_data->delta[2].u;
    output[2] = (s16) ((record_data->target[2] - delta_z)
        + ((s32) ((s16) delta_z * record_data->progress) >> 0xC));
}
