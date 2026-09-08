#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern s32 D_800814A8;


/* Collect nonzero record values, including the extra value for the selected record. */
void func_800B58B8(s32 *output, Rec_D_800E3D7C *record) {
    s32 *write_ptr;
    s32 extra_value;
    s32 first_value;
    s32 second_value;

    write_ptr = output;
    first_value = record->unk_4C.as_s32;
    if (first_value != 0) {
        *write_ptr = first_value;
        write_ptr += 1;
    }
    second_value = record->unk_50.at00_s32.v;
    if (second_value != 0) {
        *write_ptr = second_value;
        write_ptr += 1;
    }
    if (record == D_800814A8) {
        extra_value = record->unk_D8;
        if (extra_value != 0) {
            *write_ptr = extra_value;
        }
    }
}
