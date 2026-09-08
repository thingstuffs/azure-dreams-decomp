#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern s32 func_8008CFB4(s32 *);


typedef struct S_8008C4C8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C4C8_1;   /* temp_s0 in func_8008C4C8 */

/* Evaluates the summed vectors and subtracts the entry's first fixed-point component. */
s16 func_8008C4C8(Rec_func_8008ACDC_arg0 *base_vector, s32 entries, s32 entry_index) {
    s32 vector_sum[5];
    s32 result;
    s32 entry_offset;
    s32 component;
    s32 integer_component;
    S_8008C4C8_1 *entry;

    entry_offset = entry_index * 0x10;
    entry = entry_offset + entries;
    vector_sum[0] = base_vector->unk_00 + entry->unk_00;
    vector_sum[1] = base_vector->unk_04 + entry->unk_04;
    vector_sum[2] = base_vector->unk_08 + entry->unk_08;
    result = func_8008CFB4(vector_sum);
    if ((s16) result == 0x7FFF) {
        return 0x7FFF;
    }
    component = entry->unk_00;
    integer_component = component >> 0x10;
    if (component < 0) {
        component += 0xFFFF;
        integer_component = component >> 0x10;
    }
    return result - integer_component;
}
