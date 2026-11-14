#include "common.h"
#include "town/scene.h"

/* Calls blit_default_rectangle and returns zero. */
s32 blit_default_rectangle_return_zero(s32 first_value, s32 second_value, s32 third_value, s32 fourth_value) {
    blit_default_rectangle();
    return 0;
}
