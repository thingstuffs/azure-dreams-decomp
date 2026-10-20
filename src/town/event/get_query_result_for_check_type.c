#include "common.h"
#include "m2c_compat.h"

#include "engine/object/test_resident_bitmap_bit_api.h"
/* Returns the selected query result, testing for zero for check type 3. */
s32 get_query_result_for_check_type(s32 check_type)
{
    switch (check_type) {
    case 0:
        return test_resident_bitmap_bit(0x11FA);
    case 2:
        return test_resident_bitmap_bit(0x11FB);
    case 3:
        return test_resident_bitmap_bit(0x4FA) == 0;
    default:
        return 0;
    }
}
