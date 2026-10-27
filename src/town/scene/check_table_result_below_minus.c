#include "town/scene/response_checks.h"
#include "town/scene/record_queries.h"

/* Returns whether the current record value is less than -0x2F. */
s32 check_table_result_below_minus_47(void) {
    return func_8001A220() < -0x2F;
}
