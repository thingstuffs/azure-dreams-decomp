/* Slows two movement components with direction-dependent steps and clamps them at zero. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "sdk/libgte.h"
#include "sdk/libc.h"
#include "town/player.h"

/* Returns the larger of value and bound, enforcing a lower limit. */
static __inline__ s32 clamp_min(s32 value, s32 bound) { if (bound < value) return value; return bound; }

/*
 * Derives X/Y braking steps from the vector angle using sine/cosine times 32, then moves both
 * motion components toward zero without crossing it.
 */
void apply_velocity_friction(ObjectPosition *record) {
    s32 clamped_x;
    s32 clamped_y;
    s32 min_component;
    s32 signed_x_step;
    s32 signed_y_step;
    s32 reduced_x;
    s32 raised_x;
    s32 current_y;
    s32 raised_y;
    s32 reduced_y;
    s32 initial_x;
    s32 initial_y;
    s32 current_x;
    s32 y_step;
    s32 x_step;

    initial_x = record->velocity_x;
    if ((initial_x != 0) || (record->velocity_y != 0)) {
        min_component = 0x80000001;
        clamped_x = clamp_min(initial_x, min_component);
        initial_y = record->velocity_y;
        clamped_y = clamp_min(initial_y, min_component);
        x_step = ratan2(clamped_x, clamped_y);
        signed_x_step = rsin(x_step);
        y_step = x_step;
        signed_x_step = signed_x_step << 5;
        x_step = signed_x_step;
        x_step = abs(x_step);
        signed_y_step = rcos(y_step);
        signed_y_step = signed_y_step << 5;
        current_x = record->velocity_x;
        y_step = abs(signed_y_step);
        reduced_x = current_x - x_step;
        if (current_x < 0) {
            raised_x = current_x + x_step;
            record->velocity_x = raised_x;
            if (raised_x > 0) {
                record->velocity_x = 0;
            }
        } else {
            record->velocity_x = reduced_x;
            if (reduced_x < 0) {
                record->velocity_x = 0;
            }
        }
        current_y = record->velocity_y;
        if (current_y < 0) {
            raised_y = current_y + y_step;
            record->velocity_y = raised_y;
            if (raised_y > 0) {
                record->velocity_y = 0;
                return;
            }
        } else {
            reduced_y = current_y - y_step;
            record->velocity_y = reduced_y;
            if (reduced_y < 0) {
                record->velocity_y = 0;
            }
        }
    }
}
