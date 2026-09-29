#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Collect nonzero record values, including the extra value for the selected record. */
void func_800B58B8(s32 *output, EntityRec *record) {
    s32 *write_ptr;
    s32 extra_value;
    s32 first_value;
    s32 second_value;

    write_ptr = output;
    first_value = ((s32)record->unk_4C);
    if (first_value != 0) {
        *write_ptr = first_value;
        write_ptr += 1;
    }
    second_value = (*(s32 *)&record->unk_50);
    if (second_value != 0) {
        *write_ptr = second_value;
        write_ptr += 1;
    }
    if (record == ((s32)D_800814A8)) {
        extra_value = record->unk_D8;
        if (extra_value != 0) {
            *write_ptr = extra_value;
        }
    }
}
