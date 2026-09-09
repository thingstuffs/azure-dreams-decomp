#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 func_80065F90();             /* extern */
extern M2C_UNK D_80000001;


/* Move both components toward zero by direction-dependent steps, clamping at zero. */
void func_80095094(Rec_D_800E3D7C *record) {
    s32 clamped_x;
    s32 clamped_y;
    s32 min_component;
    register s32 signed_x_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 signed_y_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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

    initial_x = record->unk_0C.as_s32;
    if ((initial_x != 0) || (record->unk_10.at00_s32.v != 0)) {
        min_component = 0x80000001;
        ASM_KEEP(min_component);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        clamped_x = 0x80000001;
        if (min_component < initial_x) {
            clamped_x = initial_x;
        }
        initial_y = record->unk_10.at00_s32.v;
        clamped_y = 0x80000001;
        if (min_component < initial_y) {
            clamped_y = initial_y;
        }
        x_step = func_80065F90(clamped_x, clamped_y, min_component);
        signed_x_step = func_800644B8(x_step);
        y_step = x_step;
        signed_x_step = signed_x_step << 5;
        x_step = signed_x_step;
        if (signed_x_step < 0) {
            x_step = 0 - x_step;
        }
        signed_y_step = func_80064584(y_step);
        current_x = record->unk_0C.as_s32;
        signed_y_step = signed_y_step << 5;
        y_step = signed_y_step;
        if (signed_y_step < 0) {
            y_step = 0 - y_step;
        }
        reduced_x = current_x - x_step;
        if (current_x < 0) {
            raised_x = current_x + x_step;
            record->unk_0C.as_s32 = raised_x;
            if (raised_x > 0) {
                record->unk_0C.as_s32 = 0;
            }
        } else {
            record->unk_0C.as_s32 = reduced_x;
            if (reduced_x < 0) {
                record->unk_0C.as_s32 = 0;
            }
        }
        current_y = record->unk_10.at00_s32.v;
        if (current_y < 0) {
            raised_y = current_y + y_step;
            record->unk_10.at00_s32.v = raised_y;
            if (raised_y > 0) {
                record->unk_10.at00_s32.v = 0;
                return;
            }
        } else {
            reduced_y = current_y - y_step;
            record->unk_10.at00_s32.v = reduced_y;
            if (reduced_y < 0) {
                record->unk_10.at00_s32.v = 0;
            }
        }
    }
}
