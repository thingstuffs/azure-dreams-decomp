#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
extern int abs(int);

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 func_80065F90(s32, s32);             /* extern */


static __inline__ s32 clamp_min(s32 value, s32 bound) { if (bound < value) return value; return bound; }

/* Move both components toward zero by direction-dependent steps, clamping at zero. */
void func_80095094(EntityRec *record) {
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

    initial_x = record->unk_0C;
    if ((initial_x != 0) || (record->unk_10 != 0)) {
        min_component = 0x80000001;
        clamped_x = clamp_min(initial_x, min_component);
        initial_y = record->unk_10;
        clamped_y = clamp_min(initial_y, min_component);
        x_step = func_80065F90(clamped_x, clamped_y);
        signed_x_step = func_800644B8(x_step);
        y_step = x_step;
        signed_x_step = signed_x_step << 5;
        x_step = signed_x_step;
        x_step = abs(x_step);
        signed_y_step = func_80064584(y_step);
        signed_y_step = signed_y_step << 5;
        current_x = record->unk_0C;
        y_step = abs(signed_y_step);
        reduced_x = current_x - x_step;
        if (current_x < 0) {
            raised_x = current_x + x_step;
            record->unk_0C = raised_x;
            if (raised_x > 0) {
                record->unk_0C = 0;
            }
        } else {
            record->unk_0C = reduced_x;
            if (reduced_x < 0) {
                record->unk_0C = 0;
            }
        }
        current_y = record->unk_10;
        if (current_y < 0) {
            raised_y = current_y + y_step;
            record->unk_10 = raised_y;
            if (raised_y > 0) {
                record->unk_10 = 0;
                return;
            }
        } else {
            reduced_y = current_y - y_step;
            record->unk_10 = reduced_y;
            if (reduced_y < 0) {
                record->unk_10 = 0;
            }
        }
    }
}
