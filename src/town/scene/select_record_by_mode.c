#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"


extern M2C_UNK scene_event_buffer;
extern M2C_UNK D_8001DF1B;

/* Pick one of two global records by the selector. */
s32 *select_record_by_mode(s32 unused_a, s32 unused_b, s32 selector) {
    if (selector == 1) {
        return &D_8001DF1B;
        }
        return &scene_event_buffer;
    }
