#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

#include "engine/object/test_resident_bitmap_bit_api.h"
/* Returns the selected query result, testing for zero for check type 3. */
s32 get_query_result_for_check_type(s32 check_type)
{
    switch (check_type) {
    case 0:
        return test_resident_bitmap_bit(Fp_niko_kenkatyu);
    case 2:
        return test_resident_bitmap_bit(Fp_far_kenkatyu);
    case 3:
        return test_resident_bitmap_bit(F_sbs07_pad03) == 0;
    default:
        return 0;
    }
}
